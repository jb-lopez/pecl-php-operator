#!/usr/bin/env bash

docker build --tag pecl-php-operator .
docker run --mount type=bind,src=./output,dst=/ext-operator/output --rm -it pecl-php-operator /bin/bash
