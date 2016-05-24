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
libaf_value labaf_zero_crossing_rate (const libaf_value *signal, int size);
libaf_value labaf_significant_zero_crossing_rate (const libaf_value *signal, int size, libaf_value threshold);

#endif /* LIBAF_H_INCLUDED */
