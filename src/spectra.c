#include <af/libaf.h>
#include <atfft/atfft.h>
#include <math.h>

void libaf_magnitude_spectrum (const atfft_complex *spectrum, libaf_value *magnitudeSpectrum, int size)
{
    int maxBin = floor (size / 2) + 1;
    int i = 0;

    magnitudeSpectrum [0] = atfft_abs (spectrum [i]) / size;

    if (atfft_is_even (size))
    {
        --maxBin;
        magnitudeSpectrum [maxBin] = atfft_abs (spectrum [maxBin]) / size;
    }

    for (i = 1; i < maxBin; ++i)
    {
        magnitudeSpectrum [i] = 2.0 * atfft_abs (spectrum [i]) / size;
    }
}
