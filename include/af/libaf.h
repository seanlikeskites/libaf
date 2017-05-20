#ifndef LIBAF_H_INCLUDED
#define LIBAF_H_INCLUDED

#include <atfft/atfft_shared.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** Some typdefs for changing the type libaf works with. \cond */
#if defined(LIBAF_TYPE_FLOAT)
    typedef float af_value;

#elif defined(LIBAF_TYPE_LONG_DOUBLE)
    typedef long double af_value;

#else
#   define LIBAF_TYPE_DOUBLE
    typedef double af_value;
#endif
/** \endcond */

/* frequency conversion */
/* hertz to mel as per O'Shaughnessy (1987) */
af_value af_hertz_to_mel (af_value in);
void af_hertz_to_mel_array (const af_value *in, af_value *out, int size);
af_value af_mel_to_hertz (af_value in);
void af_mel_to_hertz_array (const af_value *in, af_value *out, int size);

/* hertz to bark as per Traunmuller (1990) */
af_value af_hertz_to_bark (af_value in);
void af_hertz_to_bark_array (const af_value *in, af_value *out, int size);
af_value af_bark_to_hertz (af_value in);
void af_bark_to_hertz_array (const af_value *in, af_value *out, int size);

/* utils */
af_value af_sum (const af_value *signal, int size);
af_value af_sum_of_squares (const af_value *signal, int size);
af_value af_product (const af_value *signal, int size);
af_value af_rms (af_value sumOfSquares, int length);

/* spectra */
void af_spectrum_frequencies (af_value *frequencies, af_value fs, int size);
void af_magnitude_spectrum (const atfft_complex *spectrum, af_value *magnitudeSpectrum, int size);

/* statistical moments */
af_value af_mean (const af_value *signal, int size);
af_value af_variance (const af_value *signal, int size, af_value mean);
af_value af_skewness (const af_value *signal, int size, af_value mean, af_value variance);
af_value af_kurtosis (const af_value *signal, int size, af_value mean, af_value variance);
void af_moments (const af_value *signal, int size, af_value *mean, af_value *variance,
                 af_value *skewness, af_value *kurtosis);

/* spectral moments */
af_value af_spectral_mean (const af_value *amplitudes, const af_value *frequencies, int size);
af_value af_spectral_variance (const af_value *amplitudes, const af_value *frequencies,
                               int size, af_value spectralMean);
af_value af_spectral_skewness (const af_value *amplitudes, const af_value *frequencies,
                               int size, af_value spectralMean, af_value spectralVariance);
af_value af_spectral_kurtosis (const af_value *amplitudes, const af_value *frequencies,
                               int size, af_value spectralMean, af_value spectralVariance);
void af_spectral_moments (const af_value *amplitudes, const af_value *frequencies, int size,
                          af_value *mean, af_value *variance,
                          af_value *skewness, af_value *kurtosis);

/* temporal things */
af_value af_zero_crossing_rate (const af_value *signal, int size);
af_value af_significant_zero_crossing_rate (const af_value *signal, int size, af_value threshold);

/* irregularity */
af_value af_krimphoff_irregularity (const af_value *amplitudes, int size);
af_value af_jensen_irregularity (const af_value *amplitudes, int size, af_value sumOfSquares);
af_value af_beauchamp_irregularity (const af_value *amplitudes, int size, af_value rms);
af_value af_spectral_flatness (af_value sum, af_value prod, int size);

/* band things */
struct af_bands
{
    int nBands;
    int *starts;
    int *widths;
    af_value **windows;
};
struct af_bands* af_alloc_bands (int nBands, int *widths);
void af_free_bands (struct af_bands *bands);
void af_sum_band_energies (const af_value *powerSpectrum, 
                           const struct af_bands *bands, 
                           af_value *bandEnergies);

/* bark band things */
struct af_bands* af_init_bark_bands (af_value fs, int size);

/* mfccs */
struct af_bands* af_init_mfccs (af_value fs, int size, af_value minFreq, af_value maxFreq, int nBands);

#ifdef __cplusplus
}
#endif

#endif /* LIBAF_H_INCLUDED */
