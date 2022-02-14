/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
    Noise function by Ken Perlin
 ***************************************************************************/
#ifndef __NOISE_H__
#define __NOISE_H__


#include "Vector2.h"
#include "Vector3.h"

//#define DELTA       0.001
//#define DELTA_INV   1000.0

//#define B   0x100
#define BM  0xf
#define N   0x100
//#define NP  12
//#define NM  0xfff



class Noise
{
    public:

        static float noise2(float2 vec);
        static inline float noise2(float x, float y);
        static float noise3(float3 vec);
        static inline float noise3(float x, float y, float z);

    private:

        static inline float at2(float rx, float ry, float* q);
        static inline float at3(float rx, float ry, float rz, float* q);
        static inline void setup(float u, int& b0, int& b1, float& r0, float& r1, float& t);

        static int p[];
        static float g[][3];
};

#include "noise.inl"


#endif
