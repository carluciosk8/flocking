/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __SPHERE_H__
#define __SPHERE_H__

#include "../Math/Vector3.h"


class Sphere
{
    public:
        Sphere();
        Sphere(float3 vCenter, float fRad);
        ~Sphere();


    protected:
        float3  m_vCenter;
        float  m_fRad;
};


#endif
