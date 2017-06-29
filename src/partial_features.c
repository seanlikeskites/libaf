#include <math.h>
#include <libaf/af.h>

int af_is_harmonic (af_value frequency, af_value f0, af_value threshold)
{
    af_value f0s = frequency / f0;
    af_value d = fabs (f0s - af_round (f0s));

    return d <= threshold;
}

int af_harmonic_partials (const af_value *partialAmplitudes, const af_value *partialFrequencies,
                          af_value *harmonicAmplitudes, af_value *harmonicFrequencies, 
                          int size, af_value f0, af_value threshold)
{
    int nHarmonics = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        if (af_is_harmonic (partialFrequencies [i], f0, threshold))
        {
            harmonicAmplitudes [nHarmonics] = partialAmplitudes [i];
            harmonicFrequencies [nHarmonics] = partialFrequencies [i];
            ++nHarmonics;
        }
    }

    return nHarmonics;
}

af_value af_inharmonicity (const af_value *powers, const af_value *frequencies,
                           int size, af_value f0)
{
    af_value num = 0, den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        af_value nearestHarmonic = f0 * af_round (frequencies [i] / f0);
        num += powers [i] * fabs (frequencies [i] - nearestHarmonic);
        den += powers [i];
    }

    return 2.0 * num / (f0 * den);
}
