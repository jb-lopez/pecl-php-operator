--TEST--
PHP Bug 56904 Testing
--EXTENSIONS--
operator
--FILE--
<?php

// This file replaces the original bug56904.phpt file.

/*
Bug 56904 was present in the original implementation of the operator extension.
In PHP 8+, attempting to run the same code will result in a fatal error instead
of a segfault. Since this is now bad PHP code, the test is expected to fail.

The expected error message is:
Fatal error: Uncaught TypeError: Unsupported operand types: string << string in %s:%d
 */

require_once __DIR__ . '/OperatorOverloading.inc';
// Constants take different code paths than scalar values, so we must test both.
const CONST_TEST = 10;
const CONST_TEXT = "Globe!";

// Testing PHP bug 56904
echo "Test Bug 56904\n";
$t56904 = new OperatorOverloading("initial");
var_dump($t56904);
$t56904->__assign_sl("abc");
var_dump($t56904);
$t56904 <<= "def";
var_dump($t56904);

--EXPECTF--
Test Bug 56904
object(OperatorOverloading)#1 (1) {
  ["value":protected]=>
  string(7) "initial"
}

Fatal error: Uncaught TypeError: Unsupported operand types: string << string in %s:%d
Stack trace:
#0 %s(%d): OperatorOverloading->__assign_sl('abc')
#1 {main}
  thrown in %s on line %d
