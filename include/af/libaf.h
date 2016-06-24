#ifndef LIBAF_H_INCLUDED
#define LIBAF_H_INCLUDED

/** Some typdefs for changing the type libaf works with. \cond */
#if defined(LIBAF_TYPE_FLOAT)
    typedef float libaf_value;

#elif defined(LIBAF_TYPE_LONG_DOUBLE)
    typedef long double libaf_value;

#else
#   define LIBAF_TYPE_DOUBLE
    typedef double libaf_value;
#endif
/** \endcond */

/* frequency conversion */
/* hertz to mel as per O'Shaughnessy (1987) */
void libaf_hertz_to_mel (const libaf_value *in, libaf_value *out, int size);
void libaf_mel_to_hertz (const libaf_value *in, libaf_value *out, int size);

/* hertz to bark as per Traunmuller (1990) */
void libaf_hertz_to_bark (const libaf_value *in, libaf_value *out, int size);
void libaf_bark_to_hertz (const libaf_value *in, libaf_value *out, int size);

/* utils */
libaf_value libaf_sum (const libaf_value *signal, int size);
libaf_value libaf_sum_of_squares (const libaf_value *signal, int size);
libaf_value libaf_product (const libaf_value *signal, int size);
libaf_value libaf_rms (libaf_value sumOfSquares, int length);

/* statistical moments */
libaf_value libaf_mean (const libaf_value *signal, int size);
libaf_value libaf_variance (const libaf_value *signal, int size, libaf_value mean);
libaf_value libaf_skewness (const libaf_value *signal, int size, libaf_value mean, libaf_value variance);
libaf_value libaf_kurtosis (const libaf_value *signal, int size, libaf_value mean, libaf_value variance);
void libaf_moments (const libaf_value *signal, int size, libaf_value *mean, libaf_value *variance,
                    libaf_value *skewness, libaf_value *kurtosis);

/* spectral moments */
libaf_value libaf_spectral_mean (const libaf_value *amplitudes, const libaf_value *frequencies, int size);
libaf_value libaf_spectral_variance (const libaf_value *amplitudes, const libaf_value *frequencies,
                                     int size, libaf_value spectralMean);
libaf_value libaf_spectral_skewness (const libaf_value *amplitudes, const libaf_value *frequencies,
                                     int size, libaf_value spectralMean, libaf_value spectralVariance);
libaf_value libaf_spectral_kurtosis (const libaf_value *amplitudes, const libaf_value *frequencies,
                                     int size, libaf_value spectralMean, libaf_value spectralVariance);
void libaf_spectral_moments (const libaf_value *amplitudes, const libaf_value *frequencies, int size,
                             libaf_value *mean, libaf_value *variance,
                             libaf_value *skewness, libaf_value *kurtosis);

/* temporal things */
libaf_value libaf_zero_crossing_rate (const libaf_value *signal, int size);
libaf_value libaf_significant_zero_crossing_rate (const libaf_value *signal, int size, libaf_value threshold);

/* irregularity */
libaf_value libaf_krimphoff_irregularity (const libaf_value *amplitudes, int size);
libaf_value libaf_jensen_irregularity (const libaf_value *amplitudes, int size, libaf_value sumOfSquares);
libaf_value libaf_beauchamp_irregularity (const libaf_value *amplitudes, int size, libaf_value rms);
libaf_value libaf_spectral_flatness (libaf_value sum, libaf_value prod, int size);

/* band things */
struct libaf_bands
{
    int nBands;
    int *bands;
};
struct libaf_bands* libaf_alloc_bands (int nBands);
void libaf_free_bands (struct libaf_bands *bands);
void libaf_sum_band_energies (const libaf_value *magnitudeSpectrum, const struct libaf_bands *bands, 
                              libaf_value *bandEnergies);

/* bark band things */
struct libaf_bands* libaf_init_bark_bands (libaf_value fs, int size);

#endif /* LIBAF_H_INCLUDED */
