--TEST--
Arithemetic Operator Testing
--EXTENSIONS--
operator
--FILE--
<?php

require_once __DIR__ . '/OperatorOverloading.inc';
// Constants take different code paths than scalar values, so we must test both.
const CONST_TEST = 10;

$a = new OperatorOverloading(10);

// Test Addition `$a::__add($b)`
echo "Test Addition\n";
var_dump($a + 2);
var_dump($a + CONST_TEST);

// Test Subtraction `$a::__sub($b)`
echo "Test Subtraction\n";
var_dump($a - 2);
var_dump($a - CONST_TEST);

// Test Multiplication `$a::__mul($b)`
echo "Test Multiplication\n";
$a->value = 5;
var_dump($a * 2);
var_dump($a * CONST_TEST);

// Test Division `$a::__div($b)`
echo "Test Division\n";
$a->value = 100;
var_dump($a / 2);
var_dump($a / CONST_TEST);

// Test Modulo `$a::__mod($b)`
echo "Test Modulo\n";
$a->value = 5;
var_dump($a % 2);
var_dump($a % CONST_TEST);

// Test Exponent `$a::__pow($b)`
echo "Test Exponent\n";
var_dump($a ** 2);
var_dump($a ** CONST_TEST);


--EXPECT--
Test Addition
int(12)
int(20)
Test Subtraction
int(8)
int(0)
Test Multiplication
int(10)
int(50)
Test Division
int(50)
int(10)
Test Modulo
int(1)
int(5)
Test Exponent
int(25)
int(9765625)
