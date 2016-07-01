#include <af/libaf.h>
#include <stdlib.h>
#include <math.h>

struct libaf_bands* libaf_init_bark_bands (libaf_value fs, int size)
{
    const int nBarkBands = 24;
    const libaf_value cutOffs[] = {20.0, 100.0, 200.0, 300.0, 400.0, 510.0,
                                   630.0, 770.0, 920.0, 1080.0, 1270.0,
                                   1480.0, 1720.0, 2000.0, 2320.0, 2700.0,
                                   3150.0, 3700.0, 4400.0, 5300.0, 6400.0,
                                   7700.0, 9500.0, 12000.0, 15500.0};
    struct libaf_bands *b;
    libaf_value nq = fs / 2.0;
    libaf_value binWidth = fs / size;
    int maxBin = floor (size / 2) + 1;
    int nBands = nBarkBands;
    int i = 0;

    /* find out how many bands can be represented by the sampling frequency */
    while (cutOffs [nBands - 1] >= nq)
    {
        --nBands;
    }

    if (!(b = libaf_alloc_bands (nBands)))
        return NULL;

    b->nBands = nBands;

    for (i = 0; i < nBands; ++i)
    {
        int bandStart = floor (cutOffs [i] / binWidth);
        int bandEnd = floor (cutOffs [i + 1] / binWidth);

        if (bandEnd > maxBin)
            bandEnd = maxBin;

        b->bands [2 * i] = bandStart;
        b->bands [2 * i + 1] = bandEnd - bandStart;
    }

    return b;
}
