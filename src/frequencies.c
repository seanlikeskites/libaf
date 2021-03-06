#include <math.h>
#include <libaf/af.h>

af_value af_hertz_to_mel (af_value in)
{
        return 1127.0 * log (1.0 + in / 700.0);
}

void af_hertz_to_mel_array (const af_value *in, af_value *out, int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        out [i] = af_hertz_to_mel (in [i]);
    }
}

af_value af_mel_to_hertz (af_value in)
{
    return 700.0 * (exp (in / 1127.0) - 1.0);
}

void af_mel_to_hertz_array (const af_value *in, af_value *out, int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        out [i] = af_mel_to_hertz (in [i]);
    }
}

af_value af_hertz_to_bark (af_value in)
{
    af_value z = (26.81 * in / (1960.0 + in)) - 0.53;

    if (z < 2.0)
        z += 0.15 * (2.0 - z);
    else if (z > 20.1)
        z += 0.22 * (z - 20.1);

    return z;
}

void af_hertz_to_bark_array (const af_value *in, af_value *out, int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        out [i] = af_hertz_to_bark (in [i]);
    }
}

af_value af_bark_to_hertz (af_value in)
{
    if (in < 2.0)
        in = (in - 0.3) / 0.85;
    else if (in > 20.1)
        in = (in + 4.422) / 1.22;

    return 1960.0 * (in + 0.53) / (26.28 - in);
}

void af_bark_to_hertz_array (const af_value *in, af_value *out, int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        out [i] = af_bark_to_hertz (in [i]);
    }
}
