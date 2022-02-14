/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __FOGSTATE_H__
#define __FOGSTATE_H__


#include "RenderState.h"
#include "../Math/Vector4.h"


class FogState : public RenderState
{
    public:
        FogState(float fStart, float fEnd, float fDensity, const float4& vrColor);
        virtual ~FogState();

        virtual void enable();
        virtual void disable();

    protected:
        int  m_iMode;
        float  m_fDensity;
        float  m_fStart;
        float  m_fEnd;
        float4  m_vColor;
};


#endif
