/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
    Multifractal function by Ken Musgrave
 ***************************************************************************/
#ifndef __MULTIFRACTAL_H__
#define __MULTIFRACTAL_H__

#include "Vector3.h"


float RidgedMultifractal(float3 point, float H, float lacunarity, float octaves, float offset, float threshold );

inline float RidgedMultifractal(float x, float y, float z,
                                float H, float lacunarity, float octaves, float offset, float threshold )
{
    return RidgedMultifractal(float3(x, y, z), H, lacunarity, octaves, offset, threshold );
}


#endif
