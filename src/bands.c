#include <libaf/af.h>
#include <stdlib.h>

struct af_bands* af_alloc_bands (int nBands, int *widths)
{
    struct af_bands *b;

    if (!(b = malloc (sizeof (*b))))
        return NULL;

    b->nBands = nBands;
    b->starts = malloc (nBands * sizeof (*(b->starts)));
    b->widths = malloc (nBands * sizeof (*(b->widths)));
    b->windows = NULL;

    if (!(b->starts && b->widths))
    {
        af_free_bands (b);
        return NULL;
    }

    if (widths)
    {
        int allocated = 1;
        int i = 0;

        if (!(b->windows = malloc (nBands * sizeof (*(b->windows)))))
        {
            af_free_bands (b);
            return NULL;
        }

        for (i = 0; i < nBands; ++i)
        {
            b->widths [i] = widths [i];

            b->windows [i] = malloc (widths [i] * sizeof (*(b->windows [i])));
            allocated = allocated && b->windows [i];
        }

        if (!allocated)
        {
            af_free_bands (b);
            return NULL;
        }
    }

    return b;
}

void af_free_bands (struct af_bands *bands)
{
    if (bands)
    {
        if (bands->windows)
        {
            int i = 0;

            for (i = 0; i < bands->nBands; ++i)
            {
                free (bands->windows [i]);
            }

            free (bands->windows);
        }

        free (bands->widths);
        free (bands->starts);
        free (bands);
    }
}

void af_sum_windowed_band_energies (const af_value *powerSpectrum, 
                                    const struct af_bands *bands, 
                                    af_value *bandEnergies)
{
    int i = 0, j = 0;

    for (i = 0; i < bands->nBands; ++i)
    {
        int bandStart = bands->starts [i];
        int bandWidth = bands->widths [i];
        af_value *window = bands->windows [i];
        af_value sum = 0.0;

        for (j = 0; j < bandWidth; ++j)
        {
            sum += window [j] * powerSpectrum [bandStart + j];
        }

        bandEnergies [i] = sum;
    }
}

void af_sum_flat_band_energies (const af_value *powerSpectrum, 
                                const struct af_bands *bands, 
                                af_value *bandEnergies)
{
    int i = 0;

    for (i = 0; i < bands->nBands; ++i)
    {
        int bandStart = bands->starts [i];
        int bandWidth = bands->widths [i];

        bandEnergies [i] = af_sum (powerSpectrum + bandStart, bandWidth);
    }
}

void af_sum_band_energies (const af_value *powerSpectrum, 
                           const struct af_bands *bands, 
                           af_value *bandEnergies)
{
    if (bands->windows)
        af_sum_windowed_band_energies (powerSpectrum, bands, bandEnergies);
    else
        af_sum_flat_band_energies (powerSpectrum, bands, bandEnergies);
}

void af_sum_band_energies_a (void **args)
{
    af_sum_band_energies ((af_value*) args [0], 
                          (struct af_bands*) args [1], 
                          (af_value*) args [2]);
}
