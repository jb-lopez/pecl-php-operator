--TEST--
Bitwise Operator Testing
--EXTENSIONS--
operator
--FILE--
<?php

require_once __DIR__ . '/OperatorOverloading.inc';
// Constants take different code paths than scalar values, so we must test both.
const CONST_TEST = 10;

$a = new OperatorOverloading(15);

// Test Bitwise And `$a::__bw_and($b)`
echo "Test Bitwise And\n";
var_dump($a & 3);
var_dump($a & CONST_TEST);

// Test Bitwise Or `$a::__bw_or($b)`
echo "Test Bitwise Or\n";
$a->value = 8;
var_dump($a | 3);
var_dump($a | CONST_TEST);

// Test Bitwise Xor `$a::__bw_xor($b)`
echo "Test Bitwise Xor\n";
var_dump($a ^ 3);
var_dump($a ^ CONST_TEST);

// Test Bitwise Shift Left `$a::__sl($b)`
echo "Test Bitwise Shift Left\n";
$a->value = 1;
var_dump($a << 1);
var_dump($a << CONST_TEST);

// Test Bitwise Shift Right `$a::__sr($b)`
echo "Test Bitwise Shift Right\n";
$a->value = 2048;
var_dump($a >> 1);
var_dump($a >> CONST_TEST);


--EXPECT--
Test Bitwise And
int(3)
int(10)
Test Bitwise Or
int(11)
int(10)
Test Bitwise Xor
int(11)
int(2)
Test Bitwise Shift Left
int(2)
int(1024)
Test Bitwise Shift Right
int(1024)
int(2)
