/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __LIGHTSTATE_H__
#define __LIGHTSTATE_H__


#include "RenderState.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"

#include <GL/glew.h>


class LightState : public RenderState
{
    public:
        LightState();
        LightState(float4 vSpecular, float4 vAmbient, float4 vDiffuse, float3 vDirection);
        virtual ~LightState();

        virtual void enable();
        virtual void disable();


	protected:
		float4  m_vSpecular;
		float4  m_vAmbient;
		float4  m_vDiffuse;
		float3  m_vDirection;

		GLfloat  m_fpPosition[4];
};


#endif
