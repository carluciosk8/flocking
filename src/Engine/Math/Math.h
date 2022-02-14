/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __MATH_H__
#define __MATH_H__

#include <cmath>
#include <cstdlib>

#ifndef M_PI
#define M_PI   3.1415926535898f
#endif

inline float fSqrt(float x)
    { return sqrtf(x); }

inline float fLogn(float x)
    { return logf(x); }

inline float fPow(float x, float y)
    { return powf(x,y); }

inline float fExp(float x)
    { return expf(x); }

inline double dSqrt(double x)
    { return sqrt(x); }

inline double dLogn(double x)
    { return log(x); }

inline double dPow(double x, double y)
    { return pow(x,y); }



inline void newSeed(int seed)
    { srand(seed); }

inline float newRand()
    { return rand()/float(RAND_MAX); }

inline float newRand(float a)
    { return a*rand()/float(RAND_MAX); }

inline float newRand(float a, float b)
    { return a + (b-a)*(rand()/float(RAND_MAX)); }



inline float fSin(float x)
    { return sinf(x); }

inline float fCos(float x)
    { return cosf(x); }

inline float fTan(float x)
    { return float(tan(x)); }

inline float fArcSin(float x)
    { return float(asin(x)); }

inline float fArcCos(float x)
    { return float(acos(x)); }

inline float fArcTan(float x)
    { return float(atan(x)); }

inline double dSin(double x)
    { return sin(x); }

inline double dCos(double x)
    { return cos(x); }

inline double dTan(double x)
    { return tan(x); }

inline double dArcSin(double x)
    { return asin(x); }

inline double dArcCos(double x)
    { return acos(x); }

inline double dArcTan(double x)
    { return atan(x); }

inline int f2Pow(int x)
    { return (1 << x); }


inline float fLerp(float a, float b, float t)
    { return a + t*(b-a); }

inline double dLerp(double a, double b, double t)
    { return a + t*(b-a); }

inline float fSpline(float t)
    { return  ( t * t * (3.0f - 2.0f * t) ); }

inline double dSpline(double t)
    { return  ( t * t * (3.0 - 2.0 * t) ); }


template <typename REAL>
        inline REAL degree(REAL rad)
{ return (180.0/M_PI)*rad; }

template <typename REAL>
        inline REAL radian(REAL deg)
{ return (M_PI/180.0)*deg; }

#define fDegree(rad)  degree<float>(rad)
#define dDegree(rad)  degree<double>(rad)


#endif //#ifndef __MATH_H__
