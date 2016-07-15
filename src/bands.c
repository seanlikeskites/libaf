#include <af/libaf.h>
#include <stdlib.h>

struct af_bands* af_alloc_bands (int nBands)
{
    struct af_bands *b;

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

void af_free_bands (struct af_bands *bands)
{
    if (bands)
    {
        free (bands->bands);
        free (bands);
    }
}

void af_sum_band_energies (const af_value *magnitudeSpectrum, const struct af_bands *bands, 
                           af_value *bandEnergies)
{
    int i = 0;

    for (i = 0; i < bands->nBands; ++i)
    {
        int bandStart = bands->bands [2 * i];
        int bandSize = bands->bands [2 * i + 1];

        bandEnergies [i] = af_sum_of_squares (magnitudeSpectrum + bandStart, bandSize);
    }
}
