<?php

require_once __DIR__ . '/tests/OperatorOverloading.inc';

/**
 * What is this file?
 *
 * This file helps with manual testing inside the PHP shell. You just need to
 * include the file and then you can test the operator overloading functionality
 * by creating instances of the `OperatorOverloading` class.
 *
 * You can run this file like so:
 *
 * ```shell
 * php -a
 * ```
 *
 * And then:
 *
 * ```php
 * require_once 'test.php';
 * $a = new OperatorOverloading("Hello");
 * $a .= " World!";
 * echo $a->value . "\n";
 * ```
 *
 * The OperatorOverloading class has all of the operators implemented, so you
 * can use it for rapid testing.
 **/
