#include <math.h>
#include <af/libaf.h>

libaf_value libaf_krimphoff_irregularity (const libaf_value *amplitudes, int size)
{
    libaf_value sum = 0;
    int i = 0;

    for (i = 1; i < (size - 1); ++i)
    {
        sum += fabs (log10 (amplitudes [i]) -
                     log10 (amplitudes [i - 1] * amplitudes [i] * amplitudes [i + 1]) / 3);
    }

    return log10 (20 * sum);
}

libaf_value libaf_jensen_irregularity (const libaf_value *amplitudes, int size, libaf_value sumOfSquares)
{
    libaf_value sum = 0;
    int i = 0;

    for (i = 0; i < (size - 1); ++i)
    {
        sum += pow (amplitudes [i] - amplitudes [i + 1], 2);
    }

    sum += amplitudes [size - 1] * amplitudes [size - 1];

    return sum / sumOfSquares;
}

libaf_value libaf_beauchamp_irregularity (const libaf_value *amplitudes, int size, libaf_value rms)
{
    libaf_value num = 0, den = 0;
    int i = 0;

    for (i = 1; i < (size - 1); ++i)
    {
        libaf_value m = (amplitudes [i - 1] + amplitudes [i] + amplitudes [i + 1]) / 3;
        num += m * fabs (amplitudes [i] - m);
        den += m;
    }

    den *= rms;

    return num / den;
}
