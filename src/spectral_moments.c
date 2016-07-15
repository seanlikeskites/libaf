#include <math.h>
#include <af/libaf.h>

af_value af_spectral_mean (const af_value *amplitudes, const af_value *frequencies, int size)
{
    af_value num = 0, den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        num += amplitudes [i] * frequencies [i];
        den += amplitudes [i];
    }

    return num / den;
}

void af_spectral_mean_a (void **args, void **results)
{
    *(af_value*) results [0] = af_spectral_mean ((af_value*) args [0], 
                                                 (af_value*) args [1],
                                                 *(int*) args [2]);
}

af_value af_spectral_variance (const af_value *amplitudes, const af_value *frequencies,
                               int size, af_value spectralMean)
{
    af_value num = 0, den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        af_value diff = frequencies [i] - spectralMean;
        num += amplitudes [i] * diff * diff;
        den += amplitudes [i];
    }

    return num / den;
}

af_value af_spectral_skewness (const af_value *amplitudes, const af_value *frequencies,
                               int size, af_value spectralMean, af_value spectralVariance)
{
    af_value num = 0, den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        af_value diff = frequencies [i] - spectralMean;
        num += amplitudes [i] * pow (diff, 3);
        den += amplitudes [i];
    }

    return num / (den * pow (spectralVariance, 1.5));
}

af_value af_spectral_kurtosis (const af_value *amplitudes, const af_value *frequencies,
                               int size, af_value spectralMean, af_value spectralVariance)
{
    af_value num = 0, den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        af_value diff = frequencies [i] - spectralMean;
        num += amplitudes [i] * pow (diff, 4);
        den += amplitudes [i];
    }

    return num / (den * spectralVariance * spectralVariance);
}

void af_spectral_moments (const af_value *amplitudes, const af_value *frequencies, int size,
                          af_value *mean, af_value *variance,
                          af_value *skewness, af_value *kurtosis)
{
    af_value m = 0, v = 0, s = 0, k = 0;
    af_value mNum = 0, vNum = 0, sNum = 0, kNum = 0;
    af_value den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        mNum += amplitudes [i] * frequencies [i];
        den += amplitudes [i];
    }

    m = mNum / den;

    for (i = 0; i < size; ++i)
    {
        af_value diff = frequencies [i] - m;
        af_value prod = diff * diff * amplitudes [i];

        vNum += prod;

        prod *= diff;
        sNum += prod;

        prod *= diff;
        kNum += prod;
    }

    v = vNum / den;
    s = sNum / (den * pow (v, 1.5));
    k = kNum / (den * v * v);

    *mean = m;
    *variance = v;
    *skewness = s;
    *kurtosis = k;
}
