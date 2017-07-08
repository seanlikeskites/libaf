#include <libaf/af.h>

void af_spectral_regression (const af_value *amplitudes, const af_value *frequencies,
                             int size, af_value *gradient, af_value *totalAmplitude)
{
    af_value a = 0.0, b = 0.0, f = 0.0, g = 0.0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        af_value amp = amplitudes [i];
        af_value freq = frequencies [i];

        a += amp;
        b += amp * freq;
        f += freq;
        g += freq * freq;
    }

    *gradient = (size * b - f * a) / (size * g - f * f);
    *totalAmplitude = a;
}

af_value af_spectral_slope (const af_value *amplitudes, const af_value *frequencies, int size)
{
    af_value m = 0.0, a = 0.0;

    af_spectral_regression (amplitudes, frequencies, size, &m, &a);

    return m / a;
}

af_value af_db_spectral_slope (const af_value *dbAmplitudes, const af_value *frequencies, int size)
{
    af_value m = 0.0, a = 0.0;

    af_spectral_regression (dbAmplitudes, frequencies, size, &m, &a);

    return m;
}

af_value af_spectral_crest (const af_value *amplitudes, int size, af_value sum)
{
    af_value max = af_max_array (amplitudes, size);
    return size * max / sum;
}

af_value af_spectral_roll_off (const af_value *powers, const af_value *frequencies,
                               int size, af_value proportion, af_value totalPower)
{
    af_value thresh = proportion * totalPower;
    af_value sum = 0.0;
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        sum += powers [i];

        if (sum >= thresh)
            break;
    }

    return frequencies [i];
}
