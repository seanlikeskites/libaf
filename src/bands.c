#include <af/libaf.h>
#include <stdlib.h>

struct libaf_bands* libaf_alloc_bands (int nBands)
{
    struct libaf_bands *b;

    if (!(b = malloc (sizeof (*b))))
        return NULL;

    if (!(b->bands = malloc (2 * nBands * sizeof (*(b->bands)))))
    {
        free (b);
        return NULL;
    }

    b->nBands = nBands;

    return b;
}

void libaf_free_bands (struct libaf_bands *bands)
{
    if (bands)
    {
        free (bands->bands);
        free (bands);
    }
}

void libaf_sum_band_energies (const libaf_value *magnitudeSpectrum, const struct libaf_bands *bands, 
                              libaf_value *bandEnergies)
{
    int i = 0;

    for (i = 0; i < bands->nBands; ++i)
    {
        int bandStart = bands->bands [2 * i];
        int bandSize = bands->bands [2 * i + 1];

        bandEnergies [i] = libaf_sum_of_squares (magnitudeSpectrum + bandStart, bandSize);
    }
}
