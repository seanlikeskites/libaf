#include <af/libaf.h>
#include <stdlib.h>
#include <math.h>

struct libaf_bark_band_limits
{
    int nLimits;
    int *limits;
};

struct libaf_bark_band_limits* libaf_init_bark_band_limits (libaf_value fs, int size)
{
    const int nLimits = 25;
    const libaf_value cutOffs[] = {20.0, 100.0, 200.0, 300.0, 400.0, 510.0,
                                   630.0, 770.0, 920.0, 1080.0, 1270.0,
                                   1480.0, 1720.0, 2000.0, 2320.0, 2700.0,
                                   3150.0, 3700.0, 4400.0, 5300.0, 6400.0,
                                   7700.0, 9500.0, 12000.0, 15500.0};
    libaf_value nq = fs / 2.0;
    struct libaf_bark_band_limits *l;
    libaf_value binWidth = fs / size;
    int maxBin = floor (size / 2);
    int i = 0;

    if (!(l = malloc (sizeof (*l))))
        return NULL;

    l->nLimits = nLimits;

    /* find out how many bands can be represented by the sampling frequency */
    while (cutOffs [l->nLimits - 2] >= nq)
    {
        --(l->nLimits);
    }

    if (!(l->limits = malloc (l->nLimits * sizeof (*(l->limits)))))
    {
        free (l);
        return NULL;
    }

    /* work out the bin numbers for those bands */

    for (i = 0; i < l->nLimits; ++i)
    {
        int binNum = floor (cutOffs [i] / binWidth);

        if (binNum > maxBin)
            binNum = maxBin;

        l->limits [i] = binNum;
    }

    return l;
}

void libaf_free_bark_band_limits (struct libaf_bark_band_limits *limits)
{
    if (limits)
    {
        free (limits->limits);
        free (limits);
    }
}
