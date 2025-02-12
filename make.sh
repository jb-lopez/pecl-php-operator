#!/usr/bin/env bash

phpize
./configure --enable-operator=shared
make
#make install
#cp modules/operator.so output/operator-"$(php -r 'echo PHP_VERSION_ID;')".so
#cp modules/operator.so output/operator.so
