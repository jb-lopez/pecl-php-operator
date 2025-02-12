--TEST--
String Operator Testing
--EXTENSIONS--
operator
--FILE--
<?php

require_once __DIR__ . '/OperatorOverloading.inc';
// Constants take different code paths than scalar values, so we must test both.
const CONST_TEXT = "Globe!";

$a = new OperatorOverloading("Hello ");


// Test Concatenation `$a::__concat($b)`
echo "Test Concatenation\n";
var_dump($a . "World!");
var_dump($a . CONST_TEXT);


--EXPECT--
Test Concatenation
string(12) "Hello World!"
string(12) "Hello Globe!"
