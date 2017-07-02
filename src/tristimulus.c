#include <libaf/af.h>

af_value af_band_proportion_of_energy (const af_value *amplitudes, const af_value *frequencies,
                                       int size, af_value lowerBound, af_value upperBound)
{
    af_value num = 0.0, den = 0.0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        af_value freq = frequencies [i];

        if ((lowerBound  <= freq) && (freq < upperBound))
                num += amplitudes [i];

        den += amplitudes [i];
    }

    return num / den;
}

af_value af_tristimulus_1 (const af_value *amplitudes, const af_value *frequencies, 
                           int size, af_value f0)
{
    af_value lb = 0.5 * f0;
    af_value ub = 1.5 * f0;

    return af_band_proportion_of_energy (amplitudes, frequencies, size, lb, ub);
}

af_value af_tristimulus_2 (const af_value *amplitudes, const af_value *frequencies,
                           int size, af_value f0)
{
    af_value lb = 1.5 * f0;
    af_value ub = 4.5 * f0;

    return af_band_proportion_of_energy (amplitudes, frequencies, size, lb, ub);
}

af_value af_tristimulus_3 (const af_value *amplitudes, const af_value *frequencies,
                           int size, af_value f0)
{
    af_value lb = 4.5 * f0;
    af_value ub = AF_VALUE_MAX;

    return af_band_proportion_of_energy (amplitudes, frequencies, size, lb, ub);
}

void af_tristimuli (const af_value *amplitudes, const af_value *frequencies, 
                    int size, af_value f0, af_value *t1, af_value *t2, af_value *t3)
{
    af_value num1 = 0.0, num2 = 0.0, num3 = 0.0;
    af_value den = 0.0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        af_value freq = frequencies [i];

        if (freq >= 4.5 * f0)
            num3 += amplitudes [i];
        else if (freq >= 1.5 * f0)
            num2 += amplitudes [i];
        else if (freq >= 0.5 * f0)
            num1 += amplitudes [i];

        den += amplitudes [i];
    }

    *t1 = num1 / den;
    *t2 = num2 / den;
    *t3 = num3 / den;
}
