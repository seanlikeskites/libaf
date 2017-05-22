#include <libaf/af.h>
#include <stdlib.h>
#include <math.h>

struct af_bands* af_init_bark_bands (af_value fs, int size)
{
    const int nBarkBands = 24;
    const af_value cutOffs[] = {20.0, 100.0, 200.0, 300.0, 400.0, 510.0,
                                630.0, 770.0, 920.0, 1080.0, 1270.0,
                                1480.0, 1720.0, 2000.0, 2320.0, 2700.0,
                                3150.0, 3700.0, 4400.0, 5300.0, 6400.0,
                                7700.0, 9500.0, 12000.0, 15500.0};
    struct af_bands *b;
    af_value nq = fs / 2.0;
    af_value binWidth = fs / size;
    int nBins = floor (size / 2) + 1;
    int nBands = nBarkBands;
    int i = 0;

    /* find out how many bands can be represented by the sampling frequency */
    while (cutOffs [nBands - 1] >= nq)
    {
        --nBands;
    }

    if (!(b = af_alloc_bands (nBands, NULL)))
        return NULL;

    for (i = 0; i < nBands; ++i)
    {
        int bandStart = floor (cutOffs [i] / binWidth + 0.5);
        int bandEnd = floor (cutOffs [i + 1] / binWidth + 0.5);

        if (bandEnd >= nBins)
            bandEnd = nBins - 1;

        b->starts [i] = bandStart;
        b->widths [i] = bandEnd - bandStart + 1;
    }

    return b;
}
