--TEST--
Bitwise Operator Testing
--EXTENSIONS--
operator
--FILE--
<?php

require_once __DIR__ . '/OperatorOverloading.inc';
// Constants take different code paths than scalar values, so we must test both.
const CONST_TEST = 10;

$a = new OperatorOverloading(10);

// Test Is Equal `$a::__is_equal($b)`
echo "Test Is Equal\n";
var_dump($a == 2);
var_dump($a == CONST_TEST);

// Test Is Identical `$a::__is_identical($b)`
echo "Test Is Identical\n";
var_dump($a === 2);
var_dump($a === CONST_TEST);

// Test Is Not Equal `$a::__is_not_equal($b)`
echo "Test Is Not Equal\n";
var_dump($a != 2);
var_dump($a != CONST_TEST);
echo "Test Is Not Equal Diamond\n";
var_dump($a <> 2);
var_dump($a <> CONST_TEST);

// Test Is Not Identical `$a::__is_not_identical($b)`
echo "Test Is Not Identical\n";
var_dump($a !== 2);
var_dump($a !== CONST_TEST);

// Test Less Than `$a::__less_than($b)`
echo "Test Less Than\n";
$a->value = 5;
var_dump($a < 2);
var_dump($a < CONST_TEST);

// Test Less Than Or Equal `$a::__less_than_or_equal($b)`
echo "Test Less Than Or Equal\n";
var_dump($a <= 2);
var_dump($a <= CONST_TEST);

// Test Spaceship Operator `$a::__spaceship($b)`
echo "Test Spaceship Operator\n";
$a->value = 5;
var_dump($a <=> 2);
var_dump($a <=> CONST_TEST);


--EXPECT--
Test Is Equal
bool(false)
bool(true)
Test Is Identical
bool(false)
bool(true)
Test Is Not Equal
bool(true)
bool(false)
Test Is Not Equal Diamond
bool(true)
bool(false)
Test Is Not Identical
bool(true)
bool(false)
Test Less Than
bool(false)
bool(true)
Test Less Than Or Equal
bool(false)
bool(true)
Test Spaceship Operator
int(1)
int(-1)
