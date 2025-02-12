# PHP Operator Overloading

This extension provides operator overloading for PHP 8.

There is an extension for operator overloading in PHP 7,
[pecl-php-operator](https://github.com/php/pecl-php-operator), but it has been
broken since PHP 7.4. This extension is a rewrite of that extension, but for
PHP 8.

## Regular Operators

These operators are the ones that make the most sense to overload. They are
assignment, unary, binary, and comparison operators.

### [Arithmetic Operators](https://www.php.net/manual/en/language.operators.arithmetic.php)

| Operator Name  | Operator   | Implemented | Function Call   |
|----------------|------------|-------------|-----------------|
| Identity       | `+$a`      | Maybe[^1]   |                 |
| Negation       | `-$a`      | Maybe[^1]   |                 |
| Addition       | `$a + $b`  | Yes         | `$a::__add($b)` |
| Subtraction    | `$a - $b`  | Yes         | `$a::__sub($b)` |
| Multiplication | `$a * $b`  | Yes         | `$a::__mul($b)` |
| Division       | `$a / $b`  | Yes         | `$a::__div($b)` |
| Modulo         | `$a % $b`  | Yes         | `$a::__mod($b)` |
| Exponent       | `$a ** $b` | Yes         | `$a::__pow($b)` |

### [Assignment Operators](https://www.php.net/manual/en/language.operators.assignment.php)

| Operator Name | Operator    | Implemented | Function Call      |
|---------------|-------------|-------------|--------------------|
| Assignment    | `$a = $b`   | Yes         | `$a::__assign($b)` |

### [Bitwise Operators](https://www.php.net/manual/en/language.operators.bitwise.php)

| Operator Name | Operator Use | Implemented | Function Call      |
|---------------|--------------|-------------|--------------------|
| And           | `$a & $b`    | Yes         | `$a::__bw_and($b)` |
| Or            | `$a \| $b`   | Yes         | `$a::__bw_or($b)`  |
| Xor           | `$a ^ $b`    | Yes         | `$a::__bw_xor($b)` |
| Not           | `~$a`        | Yes         | `$a::__bw_not($b)` |
| Shift left    | `$a << $b`   | Yes         | `$a::__sl($b)`     |
| Shift right   | `$a >> $b`   | Yes         | `$a::__sr($b)`     |

### [Comparison Operators](https://www.php.net/manual/en/language.operators.comparison.php)

| Operator Name         | Operator Use | Implemented | Function Call                   |
|-----------------------|--------------|-------------|---------------------------------|
| Equal                 | `$a == $b`   | Yes         | `$a::__is_equal($b)`            |
| Identical             | `$a === $b`  | Yes         | `$a::__is_identical($b)`        |
| Not equal             | `$a != $b`   | Yes         | `$a::__is_not_equal($b)`        |
| Not equal             | `$a <> $b`   | Yes         | `$a::__is_not_equal($b)`        |
| Not identical         | `$a !== $b`  | Yes         | `$a::__is_not_identical($b)`    |
| Less than             | `$a < $b`    | Yes         | `$a::__is_smaller($b)`          |
| Greater than          | `$a > $b`    | Yes[^4]     | `$a::__is_greater($b)`          |
| Less than or equal    | `$a <= $b`   | Yes         | `$a::__is_smaller_or_equal($b)` |
| Greater than or equal | `$a >= $b`   | Yes[^4]     | `$a::__is_greater_or_equal($b)` |
| Spaceship             | `$a <=> $b`  | Yes         | `$a::__spaceship($b)`           |
| Ternary               | `$a ?: $b`   | No          |                                 |
| Null coalescing       | `$a ?? $b`   | No[^3]      |                                 |

### [Incrementing/Decrementing Operators](https://www.php.net/manual/en/language.operators.increment.php)

| Operator Name  | Operator Use | Implemented | Function Call    |
|----------------|--------------|-------------|------------------|
| Pre-increment  | `++$a`       | Yes         | `$a::__pre_inc`  |
| Post-increment | `$a++`       | Yes         | `$a::__post_inc` |
| Pre-decrement  | `--$a`       | Yes         | `$a::__pre_dec`  |
| Post-decrement | `$a--`       | Yes         | `$a::__post_dec` |

### [Logical Operators](https://www.php.net/manual/en/language.operators.logical.php)

| Operator Name | Operator Use | Implemented | Function Call |
|---------------|--------------|-------------|---------------|
| And           | `$a and $b`  | Maybe[^1]   |               |
| Or            | `$a or $b`   | Maybe[^1]   |               |
| Xor           | `$a xor $b`  | Maybe[^1]   |               |
| Not           | `$a ! $b`    | Maybe[^1]   |               |
| And           | `$a && $b`   | Maybe[^1]   |               |
| Or            | `$a \|\| $b` | Maybe[^1]   |               |

### [String Operators](https://www.php.net/manual/en/language.operators.string.php)

| Operator Name | Operator Use | Implemented | Function Call      |
|---------------|--------------|-------------|--------------------|
| Concatenation | `$a . $b`    | Yes         | `$a::__concat($b)` |

## Combination Assignment Operators

There are a few assignment operators that are overloaded. These are an operator
and an assignment operator combined[^2]. For example, `+=` is an addition assignment
operator.

| Operator Name             | Operator Use | Implemented | Function Call             |
|---------------------------|--------------|-------------|---------------------------|
| Addition Assignment       | `$a += $b`   | Yes         | `$a::__assign_add($b)`    |
| Subtraction Assignment    | `$a -= $b`   | Yes         | `$a::__assign_sub($b)`    |
| Multiplication Assignment | `$a *= $b`   | Yes         | `$a::__assign_mul($b)`    |
| Division Assignment       | `$a /= $b`   | Yes         | `$a::__assign_div($b)`    |
| Modulo Assignment         | `$a %= $b`   | Yes         | `$a::__assign_mod($b)`    |
| Exponent Assignment       | `$a **= $b`  | Yes         | `$a::__assign_pow($b)`    |
| And Assignment            | `$a &= $b`   | Yes         | `$a::__assign_and($b)`    |
| Or Assignment             | `$a \|= $b`  | Yes         | `$a::__assign_or($b)`     |
| Xor Assignment            | `$a ^= $b`   | Yes         | `$a::__assign_xor($b)`    |
| Shift left Assignment     | `$a <<= $b`  | Yes         | `$a::__assign_sl($b)`     |
| Shift right Assignment    | `$a >>= $b`  | Yes         | `$a::__assign_sr($b)`     |
| Coalesce Assignment       | `$a ??= $b`  | No          |                           |
| Concat Assignment         | `$a .= $b`   | Yes         | `$a::__assign_concat($b)` |

## Other Opcodes

There are a number of opcodes, more than 200 in total. Many of them don't make
sense to overload. The full opcode list can be found in the `php-src` repo
[here](https://github.com/php/php-src/blob/master/Zend/zend_vm_opcodes.h#L86).

[^1]: This might be the same as other opcodes, or maybe there is no opcode for
it, but I'm not sure. I haven't tested it yet.

[^2]: There isn't a separate opcode for `+=`, it's just `ZEND_ADD` as the
`extra-details` within the `ZEND_ASSIGN_OP` opcode. Those separate opcodes were
removed in PHP 7.4. This is one of the things that broke the original operator
overloading extension.

[^3]: I've tried to implement this one, but no matter what I return the PHP
engine doesn't want to take the left hand argument. This might be kinda moot to
do though, since if an object is null-ish, it wouldn't be able to check if it's
null, right? (The object wouldn't be initialized, is what I'm getting at.) I'm
not sure what to have the function return to satisfy the PHP engine, and if I
can't write the PHP correctly, then that also means that I'd need to write up a
special documentation note just for that function to describe how to implement
it and what to return to get it to work in the userland (since I can't get it to
work in userland myself).

[^4]: Internally in the PHP engine, the `>` and `>=` operators are just the `<`
and `<=` operators with the arguments swapped. This extension swaps the operands
back to the correct order before calling the function. This might cause some
issues comparing objects to objects when not overloading the operator. Further
testing is required.
