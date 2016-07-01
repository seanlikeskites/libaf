#include <af/libaf.h>
#include <atfft/atfft.h>
#include <math.h>

void libaf_spectrum_frequencies (libaf_value *frequencies, libaf_value fs, int size)
{
    int nBins = floor (size / 2) + 1;
    libaf_value binWidth = fs / size;
    int i = 0;

    for (i = 0; i < nBins; ++i)
    {
        frequencies [i] = i * binWidth;
    }
}

void libaf_magnitude_spectrum (const atfft_complex *spectrum, libaf_value *magnitudeSpectrum, int size)
{
    int nBins = floor (size / 2) + 1;
    int i = 0;

    magnitudeSpectrum [0] = atfft_abs (spectrum [i]) / size;

    if (atfft_is_even (size))
    {
        --nBins;
        magnitudeSpectrum [nBins] = atfft_abs (spectrum [nBins]) / size;
    }

    for (i = 1; i < nBins; ++i)
    {
        magnitudeSpectrum [i] = 2.0 * atfft_abs (spectrum [i]) / size;
    }
}
