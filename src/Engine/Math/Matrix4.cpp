/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Matrix4.h"

template <> const float4x4 float4x4::IDENTITY( 1.0f , 0.0f , 0.0f , 0.0f ,
                                   0.0f , 1.0f , 0.0f , 0.0f ,
                                   0.0f , 0.0f , 1.0f , 0.0f ,
                                   0.0f , 0.0f , 0.0f , 1.0f );

template <> const double4x4 double4x4::IDENTITY( 1.0 , 0.0 , 0.0 , 0.0 ,
                                     0.0 , 1.0 , 0.0 , 0.0 ,
                                     0.0 , 0.0 , 1.0 , 0.0 ,
                                     0.0 , 0.0 , 0.0 , 1.0 );
