#include <math.h>
#include <af/libaf.h>

libaf_value libaf_sum (const libaf_value *signal, int size)
{
    libaf_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        sum += signal [i];
    }

    return sum;
}

libaf_value libaf_sum_of_squares (const libaf_value *signal, int size)
{
    libaf_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        sum += signal [i] * signal [i];
    }

    return sum;
}

libaf_value libaf_product (const libaf_value *signal, int size)
{
    libaf_value prod = 1;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        prod *= signal [i];
    }

    return prod;
}

libaf_value libaf_rms (libaf_value sumOfSquares, int length)
{
    return sqrt (sumOfSquares / length);
}
