#include <math.h>
#include <af/libaf.h>

libaf_value libaf_mean (const libaf_value *signal, int size)
{
    libaf_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        sum += signal [i];
    }

    return sum / size;
}

libaf_value libaf_variance (const libaf_value *signal, int size, libaf_value mean)
{
    libaf_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        libaf_value diff = signal [i] - mean;
        sum += diff * diff;
    }

    return sum / size;
}

libaf_value libaf_skewness (const libaf_value *signal, int size, libaf_value mean, libaf_value variance)
{
    libaf_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        libaf_value diff = signal [i] - mean;
        sum += pow (diff, 3);
    }

    return sum / (size * pow (variance, 1.5));
}

libaf_value libaf_kurtosis (const libaf_value *signal, int size, libaf_value mean, libaf_value variance)
{
    libaf_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        libaf_value diff = signal [i] - mean;
        sum += pow (diff, 4);
    }

    return sum / (size * variance * variance);
}

void libaf_moments (const libaf_value *signal, int size, libaf_value *mean, libaf_value *variance,
                    libaf_value *skewness, libaf_value *kurtosis)
{
    libaf_value m = 0, v = 0, s = 0, k = 0;
    libaf_value mSum = 0, vSum = 0, sSum = 0, kSum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        mSum += signal [i];
    }

    m = mSum / size;

    for (i = 0; i < size; ++i)
    {
        libaf_value diff = signal [i] - m;
        libaf_value prod = diff * diff;

        vSum += prod;

        prod *= diff;
        sSum += prod;

        prod *= diff;
        kSum += prod;
    }

    v = vSum / size;
    s = sSum / (size * pow (v, 1.5));
    k = kSum / (size * v * v);

    *mean = m;
    *variance = v;
    *skewness = s;
    *kurtosis = k;
}
