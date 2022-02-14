/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Matrix3.h"


template <> const float3x3 float3x3::IDENTITY( 1.0f , 0.0f , 0.0f ,
                                   0.0f , 1.0f , 0.0f ,
                                   0.0f , 0.0f , 1.0f );

template <> const double3x3 double3x3::IDENTITY( 1.0 , 0.0 , 0.0 ,
                                     0.0 , 1.0 , 0.0 ,
                                     0.0 , 0.0 , 1.0 );
