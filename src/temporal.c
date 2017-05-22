#include <assert.h>
#include <math.h>
#include <libaf/af.h>

af_value af_zero_crossing_rate (const af_value *signal, int size)
{
    int count = 0;
    int i = 0;

    for (i = 1; i < size; ++i)
    {
        if ((signal [i - 1] * signal [i]) < 0)
            ++count;
    }

    return (af_value) (count) / (size - 1);
}

void af_zero_crossing_rate_a (void **args)
{
    *(af_value*) args [0] = af_zero_crossing_rate ((af_value*) args [1], *(int*) args [2]);
}

af_value af_significant_zero_crossing_rate (const af_value *signal, int size, af_value threshold)
{
    int count = 0;
    int i = 0;
    int prevSign = signal [0] > 0.0;

    /* threshold should be positive */
    assert (threshold > 0.0);

    for (i = 1; i < (size - 1); ++i)
    {
        if (fabs (signal [i]) > threshold)
        {
            int sign = signal [i] > 0.0;

            if (sign != prevSign)
            {
                ++count;
                prevSign = sign;
            }
        }
    }

    return (af_value) (count) / (size - 1);
}

void af_significant_zero_crossing_rate_a (void **args)
{
    *(af_value*) args [0] = af_significant_zero_crossing_rate ((af_value*) args [1],
                                                                *(int*) args [2],
                                                                *(af_value*) args [3]);
}
