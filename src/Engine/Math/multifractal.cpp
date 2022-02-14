/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
    Multifractal function by Ken Musgrave
 ***************************************************************************/
#include "multifractal.h"
#include "noise.h"


float RidgedMultifractal(float3 point, float H, float lacunarity, float octaves, float offset, float threshold )
{
    float       result;
    int         i;

    /* get first octave */
    float signal = Noise::noise3(point);
    /* get absolute value of signal (this creates the ridges) */
    if (signal < 0.0f) signal = -signal;
    /* invert and translate (note that "offset" should be ~= 1.0) */
    signal = offset - signal;
    /* square the signal, to increase "sharpness" of ridges */
    signal *= signal;
    /* assign initial values */
    result = signal;
    float weight = 1.0f;

    for (i=1; weight>0.001f && i<octaves; i++)
    {
        point.x *= lacunarity;
        point.y *= lacunarity;
        point.z *= lacunarity;

        /* weight successive contributions by previous signal */
        weight = signal * threshold;
        if (weight > 1.0f) weight = 1.0f;
        if (weight < 0.0f) weight = 0.0f;
        signal = Noise::noise3(point);
        if (signal < 0.0f) signal = -signal;
        signal = offset - signal;
        signal *= signal;
        /* weight the contribution */
        signal *= weight;
        result += signal * pow(lacunarity, -i*H);
    }

    return result;
/*    float          result, signal, weight;
    int            i;

    signal = Noise::noise3( point );
    if ( signal < 0.0 ) signal = -signal;
    signal = offset - signal;
    signal *= signal;
    result = signal;
    weight = 1.0;

    for( i=1; weight>0.001 && i<octaves; i++ )
    {
        point *= lacunarity;

        weight = signal * threshold;
        if ( weight > 1.0 ) weight = 1.0;
        if ( weight < 0.0 ) weight = 0.0;
        signal = Noise::noise3( point );
        if ( signal < 0.0 ) signal = -signal;
        signal = offset - signal;
        signal *= signal;
        signal *= weight;
        result += signal * pow( lacunarity, -i*H );
    }

    return result;*/
}
