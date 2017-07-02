#ifndef LIBAF_H_INCLUDED
#define LIBAF_H_INCLUDED

#include <float.h>

#ifdef __cplusplus
extern "C"
{
#endif

/** Some typdefs for changing the type libaf works with. \cond */
#if defined(LIBAF_TYPE_FLOAT)
#   if !defined(ATFFT_TYPE_FLOAT)
#       define ATFFT_TYPE__FLOAT
#   endif
    typedef float af_value;
#   define AF_VALUE_MIX FLT_MIN
#   define AF_VALUE_MAX FLT_MAX

#elif defined(LIBAF_TYPE_LONG_DOUBLE)
#   if !defined(ATFFT_TYPE_LONG_DOUBLE)
#       define ATFFT_TYPE__LONG_DOUBLE
#   endif
    typedef long double af_value;
#   define AF_VALUE_MIX LDBL_MIN
#   define AF_VALUE_MAX LDBL_MAX

#else
#   if !defined(LIBAF_TYPE_DOUBLE)
#       define LIBAF_TYPE_DOUBLE
#   endif

#   if !defined(ATFFT_TYPE_DOUBLE)
#       define ATFFT_TYPE_DOUBLE
#   endif
    typedef double af_value;
#   define AF_VALUE_MIX DBL_MIN
#   define AF_VALUE_MAX DBL_MAX
#endif
/** \endcond */

#include <atfft/atfft_shared.h>

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
af_value af_min (af_value a, af_value b);
af_value af_max (af_value a, af_value b);
af_value af_round (af_value in);

af_value af_sum (const af_value *signal, int size);
af_value af_sum_of_squares (const af_value *signal, int size);
af_value af_product (const af_value *signal, int size);
af_value af_rms (af_value sumOfSquares, int length);

void af_square_array (const af_value *in, af_value *out, int size);
void af_log_array (const af_value *in, af_value *out, int size);

af_value af_amplitude_to_db (af_value in);
void af_amplitude_to_db_array (const af_value *in, af_value *out, int size);
af_value af_db_to_amplitude (af_value in);
void af_db_to_amplitude_array (const af_value *in, af_value *out, int size);

/* spectra */
void af_spectrum_frequencies (af_value *frequencies, af_value fs, int size);
void af_magnitude_spectrum (atfft_complex *spectrum, af_value *magnitudeSpectrum, int size);

/* statistical moments */
af_value af_mean (const af_value *signal, int size);
af_value af_variance (const af_value *signal, int size, af_value mean);
af_value af_standard_deviation (af_value variance);
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

/* partial features */
int af_spectral_partials (const af_value *ampltiudes, const af_value *frequencies,
                          af_value *partialAmplitudes, af_value *partialFrequencies,
                          int size, int separation, af_value prominence);
int af_is_harmonic (af_value frequency, af_value f0, af_value threshold);
int af_harmonic_partials (const af_value *partialAmplitudes, const af_value *partialFrequencies,
                          af_value *harmonicAmplitudes, af_value *harmonicFrequencies, 
                          int size, af_value f0, af_value threshold);
af_value af_inharmonicity (const af_value *amplitudes, const af_value *frequencies,
                           int size, af_value f0);

/* tristimulus */
af_value af_band_proportion_of_energy (const af_value *amplitudes, const af_value *frequencies,
                                       int size, af_value lowerBound, af_value upperBound);
af_value af_tristimulus_1 (const af_value *amplitudes, const af_value *frequencies, 
                           int size, af_value f0);
af_value af_tristimulus_2 (const af_value *amplitudes, const af_value *frequencies,
                           int size, af_value f0);
af_value af_tristimulus_3 (const af_value *amplitudes, const af_value *frequencies,
                           int size, af_value f0);
void af_tristimuli (const af_value *amplitudes, const af_value *frequencies, 
                    int size, af_value f0, af_value *t1, af_value *t2, af_value *t3);

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
struct af_mfcc_config;
struct af_bands* af_init_mfcc_bands (af_value fs, int size, af_value minFreq, af_value maxFreq, int nBands);
struct af_mfcc_config* af_create_mfcc_config (af_value fs, int size, 
                                              af_value minFreq, af_value maxFreq, 
                                              int nBands, int nCoeffs);
void af_destroy_mfcc_config (struct af_mfcc_config *config);
void af_mfccs (const struct af_mfcc_config *config, const af_value *powerSpectrum, af_value *mfccs);

#ifdef __cplusplus
}
#endif

#endif /* LIBAF_H_INCLUDED */
