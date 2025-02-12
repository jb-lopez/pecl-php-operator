<?php
/** @noinspection MagicMethodsValidityInspection */

class NotOverloaded
{
    protected mixed $value;

    //region Standard magic methods
    public function __get(string $name)
    {
        return $this->value;
    }

    public function __set(string $name, mixed $value)
    {
        $this->value = $value;
    }

    public function __construct(mixed $init = null)
    {
        $this->value = $init;
    }
    //endregion
}

class OperatorOverloading extends NotOverloaded
{
    //region Arithmetic Operators
    public function __add(mixed $val): mixed
    {
        return $this->value + $val;
    }

    public function __div(mixed $val): int|float
    {
        return $this->value / $val;
    }

    public function __mod(mixed $val): int
    {
        return $this->value % $val;
    }

    public function __mul(mixed $val): int|float
    {
        return $this->value * $val;
    }

    public function __pow(mixed $val): mixed
    {
        return $this->value ** $val;
    }

    public function __sub(mixed $val): mixed
    {
        return $this->value - $val;
    }
    //endregion

    //region Assignment Operators
    public function __assign(mixed $val): mixed
    {
        return $this->value = $val;
    }

    public function __assign_add(mixed $val): mixed
    {
        return $this->value += $val;
    }

    public function __assign_bw_and(mixed $val): mixed
    {
        return $this->value &= $val;
    }

    public function __assign_bw_or(mixed $val): mixed
    {
        return $this->value |= $val;
    }

    public function __assign_concat(mixed $val): string
    {
        return $this->value .= $val;
    }

    public function __assign_div(mixed $val): mixed
    {
        return $this->value /= $val;
    }

    public function __assign_mod(mixed $val): mixed
    {
        return $this->value %= $val;
    }

    public function __assign_mul(mixed $val): mixed
    {
        return $this->value *= $val;
    }

    public function __assign_pow(mixed $val): mixed
    {
        return $this->value **= $val;
    }

    public function __assign_sl(mixed $val): mixed
    {
        return $this->value <<= $val;
    }

    public function __assign_sr(mixed $val): mixed
    {
        return $this->value >>= $val;
    }

    public function __assign_sub(mixed $val): mixed
    {
        return $this->value -= $val;
    }
    //endregion

    //region Bitwise Operators
    public function __bw_and(mixed $val): int
    {
        return $this->value & $val;
    }

    public function __bw_not(): int|string
    {
        return ~$this->value;
    }

    public function __bw_or(mixed $val): int
    {
        return $this->value | $val;
    }

    public function __bw_xor(mixed $val): int
    {
        return $this->value ^ $val;
    }

    public function __sl(mixed $val): int
    {
        return $this->value << $val;
    }

    public function __sr(mixed $val): int
    {
        return $this->value >> $val;
    }
    //endregion

    //region Comparison Operators
    public function __is_equal(mixed $val): bool
    {
        return $this->value == $val;
    }

    public function __is_greater(mixed $val): bool
    {
        return $this->value > $val;
    }

    public function __is_greater_or_equal(mixed $val): bool
    {
        return $this->value >= $val;
    }

    public function __is_identical(mixed $val): bool
    {
        return $this->value === $val;
    }

    public function __is_not_equal(mixed $val): bool
    {
        return $this->value != $val;
    }

    public function __is_not_identical(mixed $val): bool
    {
        return $this->value !== $val;
    }

    public function __is_smaller(mixed $val): bool
    {
        return $this->value < $val;
    }

    public function __is_smaller_or_equal(mixed $val): bool
    {
        return $this->value <= $val;
    }

    public function __spaceship(mixed $val): int
    {
        return $this->value <=> $val;
    }
    //endregion

    //region Incrementing/Decrementing Operators
    public function __post_dec(): mixed
    {
        return $this->value--;
    }

    public function __post_inc(): mixed
    {
        return $this->value++;
    }

    public function __pre_dec(): mixed
    {
        return --$this->value;
    }

    public function __pre_inc(): mixed
    {
        return ++$this->value;
    }
    //endregion

    //region String Operators
    public function __concat(mixed $val): string
    {
        return $this->value . $val;
    }
    //endregion

}
