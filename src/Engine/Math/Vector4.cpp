/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Vector4.h"


template <> const float4 float4::ms_vZero(0.0f, 0.0f, 0.0f, 0.0f);
template <> const float4 float4::ms_vUnitX(1.0f, 0.0f, 0.0f, 0.0f);
template <> const float4 float4::ms_vUnitY(0.0f, 1.0f, 0.0f, 0.0f);
template <> const float4 float4::ms_vUnitZ(0.0f, 0.0f, 1.0f, 0.0f);
template <> const float4 float4::ms_vUnitW(0.0f, 0.0f, 0.0f, 1.0f);

template <> const double4 double4::ms_vZero(0.0, 0.0, 0.0, 0.0);
template <> const double4 double4::ms_vUnitX(1.0, 0.0, 0.0, 0.0);
template <> const double4 double4::ms_vUnitY(0.0, 1.0, 0.0, 0.0);
template <> const double4 double4::ms_vUnitZ(0.0, 0.0, 1.0, 0.0);
template <> const double4 double4::ms_vUnitW(0.0, 0.0, 0.0, 1.0);
