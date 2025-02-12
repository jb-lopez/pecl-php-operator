#ifdef HAVE_CONFIG_H

#include <zend_interfaces.h>
#include "config.h"

#endif

#include "php.h"
#include "operator.h"
#include "operator_macros.h"

static void print_zend_execute_data(const zend_execute_data *execute_data) {
    if (OpG(debug)) {
        printf(
            "ZED:\n"
            "\topline:\n"
            "\t\top1_type (zvar_type): %d (%d)\n"
            "\t\top2_type (zvar_type): %d (%d)\n"
            "\t\textended_value: %d\n"
            "\t\topcode: %d\n"
            "\t\tresult_type: %d\n"
            ,
            execute_data->opline->op1_type,
            Z_TYPE_P(zend_get_zval_ptr(execute_data->opline, execute_data->opline->op1_type, &execute_data->opline->op1, execute_data)),
            execute_data->opline->op2_type,
            Z_TYPE_P(zend_get_zval_ptr(execute_data->opline, execute_data->opline->op2_type, &execute_data->opline->op2, execute_data)),
            execute_data->opline->extended_value,
            execute_data->opline->opcode,
            execute_data->opline->result_type
        );
    }
}

static zend_bool operator_get_method(zend_string *method, zval *obj, zend_fcall_info *fci, zend_fcall_info_cache *fcc) {
    memset(fci, 0, sizeof(zend_fcall_info));
    fci->size = sizeof(zend_fcall_info);
    fci->object = Z_OBJ_P(obj);
    ZVAL_STR(&(fci->function_name), method);

    if (!zend_is_callable_ex(&(fci->function_name), fci->object, 0, NULL, fcc, NULL)) {
        return 0;
    }
    /* Disallow dispatch via __call */
    if (fcc->function_handler == Z_OBJCE_P(obj)->__call) { return 0; }
    if (fcc->function_handler->type == ZEND_USER_FUNCTION) {
        zend_op_array *oparray = (zend_op_array*)(fcc->function_handler);
        if (oparray->fn_flags & ZEND_ACC_CALL_VIA_TRAMPOLINE) {
            return 0;
        }
    }

    return 1;
}

static int handle_operator(zend_execute_data *execute_data, char *magic_method) {
    print_zend_execute_data(execute_data);
    DEBUG_PRINTF("Checking if %s is callable\n", magic_method)

    const zend_op *opline = execute_data->opline;
    zval *op1, *op2, *tmp = NULL;

    if (strcmp(magic_method, "__assign_op") == 0) {
        DEBUG_PRINTF("This is an assignment with an operation\n")
        switch (opline->extended_value) {
            ASSIGN_OPERATOR_LIST(ASSIGN_OPERATOR_METHOD_SWITCH)
            default:
                return ZEND_USER_OPCODE_DISPATCH;
        }
        DEBUG_PRINTF("magic_method is now %s\n", magic_method)
    }

    if (opline->op1_type == IS_UNUSED) {
        op1 = EX_VAR(opline->result.var);
    } else {
        op1 = zend_get_zval_ptr(execute_data->opline, execute_data->opline->op1_type, &execute_data->opline->op1, execute_data);
    }
    op2 = zend_get_zval_ptr(execute_data->opline, execute_data->opline->op2_type, &execute_data->opline->op2, execute_data);

    if ((Z_TYPE_P(op1) != IS_OBJECT)) {
        DEBUG_PRINTF("op1 is not an object\n")
        if (opline->opcode == ZEND_IS_SMALLER || opline->opcode == ZEND_IS_SMALLER_OR_EQUAL) {
            if ((Z_TYPE_P(op2) != IS_OBJECT)) {
                DEBUG_PRINTF("op2 is not an object\n")
                return ZEND_USER_OPCODE_DISPATCH;
            }
            magic_method = magic_method == "__is_smaller" ? "__is_greater" : "__is_greater_or_equal";
            DEBUG_PRINTF("magic_method is now %s\n", magic_method)
            DEBUG_PRINTF("op2 is an object, and we are using smaller ops, swap them\n")
            tmp = op1;
            op1 = op2;
            op2 = tmp;
        } else {
            return ZEND_USER_OPCODE_DISPATCH;
        }
    }

    DEBUG_PRINTF("op1 is an object\n")

    zend_fcall_info fci = empty_fcall_info;
    zend_fcall_info_cache fcc = empty_fcall_info_cache;
    zend_string * magic_method_name = zend_string_init(magic_method, strlen(magic_method), 0);

    if (!operator_get_method(magic_method_name, op1, &fci, &fcc)) {
        /* Not an overloaded call */
        DEBUG_PRINTF("Call %s is not overloaded\n", magic_method)
        return ZEND_USER_OPCODE_DISPATCH;
    }

    fci.size = sizeof(zend_fcall_info);
    fci.retval = EX_VAR(opline->result.var);
    fci.param_count = op2 ? 1 : 0;
    fci.params = op2;
    fci.object = Z_OBJ_P(op1);

    fcc.called_scope = Z_OBJCE_P(op1);
    fcc.object = Z_OBJ_P(op1);
    fcc.function_handler = zend_hash_find_ptr(&Z_OBJCE_P(op1)->function_table, magic_method_name);

    if (fcc.function_handler == NULL) {
        DEBUG_PRINTF("Function handler is null\n")
        return ZEND_USER_OPCODE_DISPATCH;
    }

    DEBUG_PRINTF("Calling %s\n", magic_method)
    if (zend_call_function(&fci, &fcc) == FAILURE) {
        DEBUG_PRINTF("Function call failed\n")
        return ZEND_USER_OPCODE_DISPATCH;
    }
    DEBUG_PRINTF("Function call succeeded\n")

    execute_data->opline++;
    return ZEND_USER_OPCODE_CONTINUE;
}

OPERATOR_LIST(OPERATOR_HANDLE)

/* {{{ operator_module_entry */
zend_module_entry operator_module_entry = {
        STANDARD_MODULE_HEADER,
        "operator",                    /* Extension name */
        NULL,                           /* zend_function_entry */
        PHP_MINIT(operator),           /* PHP_MINIT - Module initialization */
        PHP_MSHUTDOWN(operator),       /* PHP_MSHUTDOWN - Module shutdown */
        NULL,                           /* PHP_RINIT - Request initialization */
        NULL,                           /* PHP_RSHUTDOWN - Request shutdown */
        PHP_MINFO(operator),           /* PHP_MINFO - Module info */
        PHP_OPERATOR_VERSION,          /* Version */
        STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_OPERATOR
# ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
# endif

ZEND_GET_MODULE(operator)

#endif
