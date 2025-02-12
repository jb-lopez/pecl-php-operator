FROM php:8.4-bookworm

RUN apt install -y $PHPIZE_DEPS

COPY --from=composer:latest /usr/bin/composer /usr/local/bin/composer

COPY . /ext-operator
COPY ./ext-operator.ini /usr/local/etc/php/conf.d/ext-operator.ini

WORKDIR /ext-operator
