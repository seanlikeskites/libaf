#include <math.h>
#include <af/libaf.h>

void libaf_hertz_to_mel (const libaf_value *in, libaf_value *out, int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        out [i] = 1127.0 * log (1.0 + in [i] / 700.0);
    }
}

void libaf_mel_to_hertz (const libaf_value *in, libaf_value *out, int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        out [i] = 700.0 * (exp (in [i] / 1127.0) - 1);
    }
}

static inline libaf_value libaf_hertz_to_bark_single (libaf_value in)
{
    libaf_value z = (26.81 * in / (1960.0 + in)) - 0.53;

    if (z < 2.0)
        z += 0.15 * (2 - z);
    else if (z > 20.1)
        z += 0.22 * (z - 20.1);

    return z;
}

void libaf_hertz_to_bark (const libaf_value *in, libaf_value *out, int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        out [i] = libaf_hertz_to_bark_single (in [i]);
    }
}

static inline libaf_value libaf_bark_to_hertz_single (libaf_value in)
{
    if (in < 2.0)
        in = (in - 0.3) / 0.85;
    else if (in > 20.1)
        in = (in + 4.422) / 1.22;

    return 1960.0 * (in + 0.53) / (26.28 - in);
}

void libaf_bark_to_hertz (const libaf_value *in, libaf_value *out, int size)
{
    int i = 0;

    for (i = 0; i < size; ++i)
    {
        out [i] = libaf_bark_to_hertz_single (in [i]);
    }
}
