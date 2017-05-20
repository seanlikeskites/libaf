#include <af/libaf.h>
#include <atfft/atfft_dct.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void af_generate_mfcc_window (af_value *window, int middle, int end, int width)
{
    int riseWidth = middle;
    af_value mRise = 1.0 / riseWidth;
    int fallWidth = end - middle;
    af_value mFall = -1.0 / fallWidth;
    int i = 0;

    for (i = 0; i < middle; ++i)
    {
        window [i] = mRise * i;
    }

    for (i = middle; i < width; ++i)
    {
        window [i] = 1.0 + mFall * (i - middle);
    }
}

struct af_bands* af_init_mfcc_bands (af_value fs, int size, af_value minFreq, af_value maxFreq, int nBands)
{
    af_value binWidth = fs / size;
    int nBins = floor (size / 2) + 1;
    af_value minMel = af_hertz_to_mel (minFreq);
    af_value maxMel = af_hertz_to_mel (maxFreq);
    af_value melRange = maxMel - minMel;
    int nBounds = nBands + 2;
    af_value m = melRange / (nBounds - 1);

    int lastBin = 0;
    af_value *bounds = malloc (nBounds * sizeof (*bounds));
    int *widths = malloc (nBands * sizeof (*widths));

    if (!(bounds && widths))
    {
        free (widths);
        free (bounds);
        return NULL;
    }

    struct af_bands *b;

    int i = 0;

    /* calculate band boundaries */
    for (i = 0; i < nBounds; ++i)
    {
        af_value melFreq = m * i + minMel;
        af_value freq = af_mel_to_hertz (melFreq);
        lastBin = floor (freq / binWidth + 0.5);
        bounds [i] = lastBin;

        if (lastBin >= nBins)
        {
            bounds [i] = nBins - 1;
            nBounds = i + 1;
            nBands = nBounds - 2;
            break;
        }
    }

    /* calculate band widths */
    for (i = 0; i < nBands; ++i)
    {
        widths [i] = bounds [i + 2] - bounds [i] + 1;
    }

    /* allocate the bands */
    b = af_alloc_bands (nBands, widths);

    /* calculate envelopes */
    for (i = 0; i < nBands; ++i)
    {
        int start = bounds [i];
        int middle = bounds [i + 1] - start;
        int end = bounds [i + 2] - start;

        if (i == nBands - 1)
            end = lastBin - start;            

        b->starts [i] = start;
        af_generate_mfcc_window (b->windows [i], middle, end, b->widths [i]);
    }

    free (widths);
    free (bounds);

    return b;
}

struct af_mfcc_config
{
    int nCoeffs;
    struct af_bands *bands;
    struct atfft_dct *dct;
    af_value *bandEnergies;
    af_value *dctCoeffs;
};

struct af_mfcc_config* af_create_mfcc_config (af_value fs, int size, af_value minFreq, af_value maxFreq, int nBands, int nCoeffs)
{
    struct af_mfcc_config *c;

    if (!(c = malloc (sizeof (*c))))
        return NULL;

    c->bands = af_init_mfcc_bands (fs, size, minFreq, maxFreq, nBands);
    c->dct = NULL;
    c->bandEnergies = NULL;
    c->dctCoeffs = NULL;

    if (!c->bands)
    {
        af_destroy_mfcc_config (c);
        return NULL;
    }

    nBands = c->bands->nBands;
    c->dct = atfft_dct_create (nBands, ATFFT_FORWARD);
    c->bandEnergies = malloc (nBands * sizeof (*(c->bandEnergies)));
    c->dctCoeffs = malloc (nBands * sizeof (*(c->dctCoeffs)));

    if (!(c->dct && c->bandEnergies && c->dctCoeffs))
    {
        af_destroy_mfcc_config (c);
        return NULL;
    }

    if (nCoeffs > nBands)
        c->nCoeffs = nBands;
    else
        c->nCoeffs = nCoeffs;

    return c;
}

void af_destroy_mfcc_config (struct af_mfcc_config *config)
{
    if (config)
    {
        free (config->dctCoeffs);
        free (config->bandEnergies);
        atfft_dct_destroy (config->dct);
        af_free_bands (config->bands);
        free (config);
    }
}

void af_mfccs (const struct af_mfcc_config *config, const af_value *powerSpectrum, af_value *mfccs)
{
    int nBands = config->bands->nBands;
    int nCoeffs = config->nCoeffs;
    int dataSize = nCoeffs * sizeof (*mfccs);

    af_sum_band_energies (powerSpectrum, config->bands, config->bandEnergies);
    af_log_array (config->bandEnergies, config->bandEnergies, nBands);
    atfft_dct_transform (config->dct, config->bandEnergies, config->dctCoeffs);
    memcpy (mfccs, config->dctCoeffs, dataSize);
}
