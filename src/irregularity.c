#include <math.h>
#include <af/libaf.h>

af_value af_krimphoff_irregularity (const af_value *amplitudes, int size)
{
    af_value sum = 0;
    int i = 0;

    for (i = 1; i < (size - 1); ++i)
    {
        sum += fabs (log10 (amplitudes [i]) -
                     log10 (amplitudes [i - 1] * amplitudes [i] * amplitudes [i + 1]) / 3);
    }

    return log10 (20 * sum);
}

af_value af_jensen_irregularity (const af_value *amplitudes, int size, af_value sumOfSquares)
{
    af_value sum = 0;
    int i = 0;

    for (i = 0; i < (size - 1); ++i)
    {
        sum += pow (amplitudes [i] - amplitudes [i + 1], 2);
    }

    sum += amplitudes [size - 1] * amplitudes [size - 1];

    return sum / sumOfSquares;
}

af_value af_beauchamp_irregularity (const af_value *amplitudes, int size, af_value rms)
{
    af_value num = 0, den = 0;
    int i = 0;

    for (i = 1; i < (size - 1); ++i)
    {
        af_value m = (amplitudes [i - 1] + amplitudes [i] + amplitudes [i + 1]) / 3;
        num += m * fabs (amplitudes [i] - m);
        den += m;
    }

    den *= rms;

    return num / den;
}

af_value af_spectral_flatness (af_value sum, af_value prod, int size)
{
    af_value num = size * pow (prod, 1.0 / (af_value) size);
    return num / sum;
}
