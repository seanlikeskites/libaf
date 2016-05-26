#include <assert.h>
#include <math.h>
#include <af/libaf.h>

libaf_value libaf_zero_crossing_rate (const libaf_value *signal, int size)
{
    int count = 0;
    int i = 0;

    for (i = 1; i < size; ++i)
    {
        if ((signal [i - 1] * signal [i]) < 0)
            ++count;
    }

    return (libaf_value) (count) / (size - 1);
}

libaf_value libaf_significant_zero_crossing_rate (const libaf_value *signal, int size, libaf_value threshold)
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

    return (libaf_value) (count) / (size - 1);
}
