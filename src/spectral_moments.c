#include <math.h>
#include <af/libaf.h>

libaf_value libaf_spectral_mean (const libaf_value *amplitudes, const libaf_value *frequencies, int size)
{
    libaf_value num = 0, den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        num += amplitudes [i] * frequencies [i];
        den += amplitudes [i];
    }

    return num / den;
}

libaf_value libaf_spectral_variance (const libaf_value *amplitudes, const libaf_value *frequencies,
                                     int size, libaf_value spectralMean)
{
    libaf_value num = 0, den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        libaf_value diff = frequencies [i] - spectralMean;
        num += amplitudes [i] * diff * diff;
        den += amplitudes [i];
    }

    return num / den;
}

libaf_value libaf_spectral_skewness (const libaf_value *amplitudes, const libaf_value *frequencies,
                                     int size, libaf_value spectralMean, libaf_value spectralVariance)
{
    libaf_value num = 0, den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        libaf_value diff = frequencies [i] - spectralMean;
        num += amplitudes [i] * pow (diff, 3);
        den += amplitudes [i];
    }

    return num / (den * pow (spectralVariance, 1.5));
}

libaf_value libaf_spectral_kurtosis (const libaf_value *amplitudes, const libaf_value *frequencies,
                                     int size, libaf_value spectralMean, libaf_value spectralVariance)
{
    libaf_value num = 0, den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        libaf_value diff = frequencies [i] - spectralMean;
        num += amplitudes [i] * pow (diff, 4);
        den += amplitudes [i];
    }

    return num / (den * spectralVariance * spectralVariance);
}

void libaf_spectral_moments (const libaf_value *amplitudes, const libaf_value *frequencies, int size,
                             libaf_value *mean, libaf_value *variance,
                             libaf_value *skewness, libaf_value *kurtosis)
{
    libaf_value m = 0, v = 0, s = 0, k = 0;
    libaf_value mNum = 0, vNum = 0, sNum = 0, kNum = 0;
    libaf_value den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        mNum += amplitudes [i] * frequencies [i];
        den += amplitudes [i];
    }

    m = mNum / den;

    for (i = 0; i < size; ++i)
    {
        libaf_value diff = frequencies [i] - m;
        libaf_value prod = diff * diff * amplitudes [i];

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
