--TEST--
Incrementing/Decrementing Operator Testing
--EXTENSIONS--
operator
--FILE--
<?php

require_once __DIR__ . '/OperatorOverloading.inc';
// Constants take different code paths than scalar values, so we must test both.
const CONST_TEST = 10;

$a = new OperatorOverloading(10);
// Test Pre-Increment `$a::__pre_inc()`
echo "Test Pre-Increment\n";
var_dump($a->value);
var_dump(++$a);
var_dump($a->value);

// Test Post-Increment `$a::__post_inc()`
echo "Test Post-Increment\n";
var_dump($a->value);
var_dump($a++);
var_dump($a->value);

// Test Pre-Decrement `$a::__pre_dec()`
echo "Test Pre-Decrement\n";
var_dump($a->value);
var_dump(--$a);
var_dump($a->value);

// Test Post-Decrement `$a::__post_dec()`
echo "Test Post-Decrement\n";
var_dump($a->value);
var_dump($a--);
var_dump($a->value);


--EXPECT--
Test Pre-Increment
int(10)
int(11)
int(11)
Test Post-Increment
int(11)
int(11)
int(12)
Test Pre-Decrement
int(12)
int(11)
int(11)
Test Post-Decrement
int(11)
int(11)
int(10)
