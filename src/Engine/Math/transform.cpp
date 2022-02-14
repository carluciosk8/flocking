/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "transform.h"
#include "Math.h"


void rotateX(float3x3& m, float a)
{
    float cos_a = fCos(a);
    float sin_a = fSin(a);
    m.m[0][0] = 1.0f ; m.m[0][1] = 0.0f  ; m.m[0][2] =  0.0f;
    m.m[1][0] = 0.0f ; m.m[1][1] = cos_a ; m.m[1][2] = -sin_a;
    m.m[2][0] = 0.0f ; m.m[2][1] = sin_a ; m.m[2][2] =  cos_a;
}



void rotateY(float3x3& m, float a)
{
    float cos_a = fCos(a);
    float sin_a = fSin(a);
    m.m[0][0] =  cos_a ; m.m[0][1] = 0.0f ; m.m[0][2] = sin_a;
    m.m[1][0] =  0.0f  ; m.m[1][1] = 1.0f ; m.m[1][2] = 0.0f;
    m.m[2][0] = -sin_a ; m.m[2][1] = 0.0f ; m.m[2][2] = cos_a;
}



void rotateZ(float3x3& m, float a)
{
    float cos_a = fCos(a);
    float sin_a = fSin(a);
    m.m[0][0] = cos_a ; m.m[0][1] = -sin_a ; m.m[0][2] = 0.0f;
    m.m[1][0] = sin_a ; m.m[1][1] =  cos_a ; m.m[1][2] = 0.0f;
    m.m[2][0] = 0.0f  ; m.m[2][1] =  0.0f  ; m.m[2][2] = 1.0f;
}



void rotateYXZ(float3x3& m, float y, float p, float r)
{
    float cz = fCos(r);
    float cy = fCos(y);
    float cx = fCos(p);
    float sz = fSin(r);
    float sy = fSin(y);
    float sx = fSin(p);

    m.m[0][0] = cy*cz + sx*sy*sz;  m.m[0][1] = cz*sx*sy - cy*sz;  m.m[0][2] = cx*sy;
    m.m[1][0] = cx*sz;             m.m[1][1] = cx*cz;             m.m[1][2] = -sx;
    m.m[2][0] = cy*sx*sz - cz*sy;  m.m[2][1] = cy*cz*sx + sy*sz;  m.m[2][2] = cx*cy;
}
