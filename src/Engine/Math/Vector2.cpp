/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Vector2.h"


template <> const float2 float2::ZERO(0.0f, 0.0f);
template <> const float2 float2::UNIT_X(1.0f, 0.0f);
template <> const float2 float2::UNIT_Y(0.0f, 1.0f);

template <> const double2 double2::ZERO(0.0, 0.0);
template <> const double2 double2::UNIT_X(1.0, 0.0);
template <> const double2 double2::UNIT_Y(0.0, 1.0);
