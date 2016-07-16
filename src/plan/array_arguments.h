#ifndef ARRAY_ARGUMENTS_H_INCLUDED
#define ARRAY_ARGUMENTS_H_INCLUDED

#ifdef __cplusplus
extern "C"
{
#endif

/* utils */
void af_sum_a (void **args);
void af_sum_of_squares_a (void **args);
void af_product_a (void **args);
void af_rms_a (void **args);

/* spectra */
void af_magnitude_spectrum_a (void **args);

/* statistical moments */
void af_mean_a (void **args);
void af_variance_a (void **args);
void af_skewness_a (void **args);
void af_kurtosis_a (void **args);
void af_moments_a (void **args);

/* spectral moments */
void af_spectral_mean_a (void **args);
void af_spectral_variance_a (void **args);
void af_spectral_skewness_a (void **args);
void af_spectral_kurtosis_a (void **args);
void af_spectral_moments_a (void **args);

/* temporal things */
void af_zero_crossing_rate_a (void **args);
void af_significant_zero_crossing_rate_a (void **args);

/* irregularity */
void af_krimphoff_irregularity_a (void **args);
void af_jensen_irregularity_a (void **args);
void af_beauchamp_irregularity_a (void **args);
void af_spectral_flatness_a (void **args);

/* band things */
void af_sum_band_energies_a (void **args);

#ifdef __cplusplus
}
#endif

#endif /* ARRAY_ARGUMENTS_H_INCLUDED */
