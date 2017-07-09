#include <math.h>
#include <libaf/af.h>

int af_is_peak (const af_value *amplitudes, int size, int idx, 
                int separation, af_value prominence, int *step)
{
    int k;
    int start, end, len;
    af_value m, s;
    af_value amp = amplitudes [idx];

    /* return early if we are on a negative gradient portion */
    if (amp <= amplitudes [idx - 1])
        return 0;

    /* check if the peak meets separation requirements */
    end = af_min (size, idx + separation + 1);

    for (k = idx + 1; k < end; ++k)
    {
        if (amplitudes [k] > amp)
        {
            *step = k;
            return 0;
        }
    }

    /* check if the peak meets prominence requirements */
    start = af_max (0, idx - separation);
    len = end - start;
    m = af_mean (amplitudes + start, len);
    s = af_standard_deviation (af_variance (amplitudes + start, len, m));
    *step = separation + 1;

    if ((amp - m) >= (prominence * s))
        return 1;
    else
        return 0;
}

int af_spectral_partials (const af_value *amplitudes, const af_value *frequencies,
                          af_value *partialAmplitudes, af_value *partialFrequencies,
                          int size, int separation, af_value prominence)
{
    int nPartials = 0;
    int i = 1;

    while (i < size - 1)
    {
        int step = 1;

        if (af_is_peak (amplitudes, size, i, separation, prominence, &step))
        {
            partialAmplitudes [nPartials] = amplitudes [i];
            partialFrequencies [nPartials] = frequencies [i];
            ++nPartials;
        }

        i += step;
    }

    return nPartials;
}

af_value af_inharmonicity (const af_value *powers, const af_value *frequencies,
                           int size, af_value f0)
{
    af_value num = 0, den = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        af_value freq = frequencies [i];
        af_value nearestHarmonicFreq = f0 * af_round (freq / f0);

        num += powers [i] * fabs (freq - nearestHarmonicFreq);
        den += powers [i];
    }

    return 2.0 * num / (f0 * den);
}

int af_is_harmonic (af_value frequency, af_value f0, af_value threshold, int *order)
{
    af_value d = 0.0;
    af_value f0s = frequency / f0;

    *order = af_round (f0s);
    d = fabs (f0s - *order);

    return (d <= threshold) && (*order > 0);
}

void af_harmonic_powers (const af_value *powers, const af_value *frequencies, int size,
                         af_value *harmonicPowers, int maxOrder,
                         af_value f0, af_value threshold)
{
    int i = 0;

    af_zero_array (harmonicPowers, maxOrder);

    for (i = 0; i < size; ++i)
    {
        af_value freq = frequencies [i];
        int harmonic = 0;
        int order = 0;

        af_is_harmonic (freq, f0, threshold, &order);

        if (order > maxOrder)
            break;
        else if (harmonic)
            harmonicPowers [order - 1] += powers [i];
    }
}

int af_harmonic_partials (const af_value *partialAmplitudes, const af_value *partialFrequencies,
                          af_value *harmonicAmplitudes, af_value *harmonicFrequencies, int *harmonicOrders,
                          int size, af_value f0, af_value threshold)
{
    int nHarmonics = 0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        int order = 0;

        if (af_is_harmonic (partialFrequencies [i], f0, threshold, &order))
        {
            harmonicAmplitudes [nHarmonics] = partialAmplitudes [i];
            harmonicFrequencies [nHarmonics] = partialFrequencies [i];
            harmonicOrders [nHarmonics] = order;
            ++nHarmonics;
        }
    }

    return nHarmonics;
}

