#include <math.h>
#include <libaf/af.h>

af_value af_round (af_value in)
{
    if (in >= 0.0)
        return floor (in + 0.5);
    else
        return ceil (in - 0.5);
}

af_value af_sum (const af_value *signal, int size)
{
    af_value sum = 0.0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        sum += signal [i];
    }

    return sum;
}

void af_sum_a (void **args)
{
    *(af_value*) args [0] = af_sum ((af_value*) args [1], *(int*) args [2]);
}

af_value af_sum_of_squares (const af_value *signal, int size)
{
    af_value sum = 0.0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        sum += signal [i] * signal [i];
    }

    return sum;
}

void af_sum_of_squares_a (void **args)
{
    *(af_value*) args [0] = af_sum_of_squares ((af_value*) args [1], *(int*) args [2]);
}

af_value af_product (const af_value *signal, int size)
{
    af_value prod = 1.0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        prod *= signal [i];
    }

    return prod;
}

void af_product_a (void **args)
{
    *(af_value*) args [0] = af_product ((af_value*) args [1], *(int*) args [2]);
}

af_value af_rms (af_value sumOfSquares, int length)
{
    return sqrt (sumOfSquares / length);
}

void af_rms_a (void **args)
{
    *(af_value*) args [0] = af_rms (*(af_value*) args [1], *(int*) args [2]);
}

void af_square_array (const af_value *in, af_value *out, int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        out [i] = in [i] * in [i];
    }
}

void af_log_array (const af_value *in, af_value *out, int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        out [i] = log (in [i]);
    }
}
