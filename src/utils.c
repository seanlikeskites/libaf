#include <math.h>
#include <af/libaf.h>

af_value af_sum (const af_value *signal, int size)
{
    af_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        sum += signal [i];
    }

    return sum;
}

af_value af_sum_of_squares (const af_value *signal, int size)
{
    af_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        sum += signal [i] * signal [i];
    }

    return sum;
}

af_value af_product (const af_value *signal, int size)
{
    af_value prod = 1;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        prod *= signal [i];
    }

    return prod;
}

af_value af_rms (af_value sumOfSquares, int length)
{
    return sqrt (sumOfSquares / length);
}
