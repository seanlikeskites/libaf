#include <math.h>
#include <libaf/af.h>

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

void af_krimphoff_irregularity_a (void **args)
{
    *(af_value*) args [0] = af_krimphoff_irregularity ((af_value*) args [1], *(int*) args [2]);
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

void af_jensen_irregularity_a (void **args)
{
    *(af_value*) args [0] = af_jensen_irregularity ((af_value*) args [1],
                                                    *(int*) args [2],
                                                    *(af_value*) args [3]);
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

void af_beauchamp_irregularity_a (void **args)
{
    *(af_value*) args [0] = af_beauchamp_irregularity ((af_value*) args [1],
                                                       *(int*) args [2],
                                                       *(af_value*) args [3]);
}

af_value af_spectral_flatness (af_value sum, af_value prod, int size)
{
    af_value num = size * pow (prod, 1.0 / (af_value) size);
    return num / sum;
}

void af_spectral_flatness_a (void **args)
{
    *(af_value*) args [0] = af_spectral_flatness (*(af_value*) args [1],
                                                  *(af_value*) args [2],
                                                  *(int*) args [3]);
}
