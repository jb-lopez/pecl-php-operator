#!/usr/bin/env bash

# The PHP version is the first argument
PHP_VERSION=$1
# If the version is 8.0 we need to use bullseye, if it's 8.1+ we can use bookworm
if [[ "$PHP_VERSION" == "8.0"* ]]; then
    BASE_IMAGE="$PHP_VERSION-bullseye"
else
    BASE_IMAGE="$PHP_VERSION-bookworm"
fi

docker build --tag pecl-php-operator . --build-arg PHP_VERSION="$BASE_IMAGE"
docker run --mount type=bind,src=./output,dst=/ext-operator/output --rm -it pecl-php-operator /bin/bash
