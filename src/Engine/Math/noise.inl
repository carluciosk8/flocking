/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
    Noise function by Ken Perlin
 ***************************************************************************/
float Noise::noise2(float x, float y)
{
    return noise2( float2(x, y) );
}



float Noise::noise3(float x, float y, float z)
{
    return noise3( float3(x, y, z) );
}



inline float Noise::at2(float rx, float ry, float* q)
{
    return  ( rx * q[0] + ry * q[1] );
}


inline float Noise::at3(float rx, float ry, float rz, float* q)
{
    return  ( rx * q[0] + ry * q[1] + rz * q[2] );
}


inline void Noise::setup(float u, int& b0, int& b1, float& r0, float& r1, float& t)
{
    t = u + N;
    b0 = ((int)t) & BM;
    b1 = (b0+1) & BM;
    r0 = t - (int)t;
    r1 = r0 - 1.0f;
}
