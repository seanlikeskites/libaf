#include <af/libaf.h>
#include <stdlib.h>

void af_init_mfccs (af_value fs, int size, af_value minFreq, af_value maxFreq, int nBands)
{
    af_value minMel = af_hertz_to_mel (minFreq);
    af_value maxMel = af_hertz_to_mel (maxFreq);
    af_value melRange = maxMel - minMel;
    int nBounds = nBands + 2;
    af_value m = melRange / (nBounds - 1);

    /* af_value *dftBounds = malloc (nBounds * sizeof (*dftBounds)); */

    int i = 0;

    for (i = 0; i < nBounds; ++i)
    {
        af_value melFreq = m * i + minMel;
        af_value freq = af_mel_to_hertz (melFreq);
    }
}
