/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Vector3.h"


template <> const float3 float3::ZERO(0.0f,0.0f,0.0f);
template <> const float3 float3::UNIT_X(1.0f,0.0f,0.0f);
template <> const float3 float3::UNIT_Y(0.0f,1.0f,0.0f);
template <> const float3 float3::UNIT_Z(0.0f,0.0f,1.0f);

template <> const double3 double3::ZERO(0.0, 0.0, 0.0);
template <> const double3 double3::UNIT_X(1.0, 0.0, 0.0);
template <> const double3 double3::UNIT_Y(0.0, 1.0, 0.0);
template <> const double3 double3::UNIT_Z(0.0, 0.0, 1.0);
