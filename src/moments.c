#include <math.h>
#include <libaf/af.h>

af_value af_mean (const af_value *signal, int size)
{
    af_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        sum += signal [i];
    }

    return sum / size;
}

void af_mean_a (void **args)
{
    *(af_value*) args [0] = af_mean ((af_value*) args [1], 
                                     *(int*) args [2]);
}

af_value af_variance (const af_value *signal, int size, af_value mean)
{
    af_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        af_value diff = signal [i] - mean;
        sum += diff * diff;
    }

    return sum / size;
}

void af_variance_a (void **args)
{
    *(af_value*) args [0] = af_variance ((af_value*) args [1], 
                                         *(int*) args [2],
                                         *(af_value*) args [3]);
}

af_value af_skewness (const af_value *signal, int size, af_value mean, af_value variance)
{
    af_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        af_value diff = signal [i] - mean;
        sum += pow (diff, 3);
    }

    return sum / (size * pow (variance, 1.5));
}

void af_skewness_a (void **args)
{
    *(af_value*) args [0] = af_skewness ((af_value*) args [1], 
                                         *(int*) args [2],
                                         *(af_value*) args [3],
                                         *(af_value*) args [4]);
}

af_value af_kurtosis (const af_value *signal, int size, af_value mean, af_value variance)
{
    af_value sum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        af_value diff = signal [i] - mean;
        sum += pow (diff, 4);
    }

    return sum / (size * variance * variance);
}

void af_kurtosis_a (void **args)
{
    *(af_value*) args [0] = af_kurtosis ((af_value*) args [1], 
                                         *(int*) args [2],
                                         *(af_value*) args [3],
                                         *(af_value*) args [4]);
}

void af_moments (const af_value *signal, int size, af_value *mean, af_value *variance,
                 af_value *skewness, af_value *kurtosis)
{
    af_value m = 0, v = 0, s = 0, k = 0;
    af_value mSum = 0, vSum = 0, sSum = 0, kSum = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        mSum += signal [i];
    }

    m = mSum / size;

    for (i = 0; i < size; ++i)
    {
        af_value diff = signal [i] - m;
        af_value prod = diff * diff;

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

void af_moments_a (void **args)
{
    af_moments ((af_value*) args [0], *(int*) args [1], 
                (af_value*) args [2], (af_value*) args [3], (af_value*) args [4], (af_value*) args [5]);
}
