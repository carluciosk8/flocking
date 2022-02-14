/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "LightState.h"


#include <cstdio>


LightState::LightState()
{}



LightState::LightState(float4 vSpecular, float4 vAmbient, float4 vDiffuse, float3 vDirection)
:
	m_vSpecular(vSpecular),
	m_vAmbient(vAmbient),
	m_vDiffuse(vDiffuse),
	m_vDirection(vDirection)
{
	m_fpPosition[0] = m_vDirection.x;
	m_fpPosition[1] = m_vDirection.y;
	m_fpPosition[2] = m_vDirection.z;
	m_fpPosition[3] = 0.0f;
}



LightState::~LightState()
{}



void LightState::enable()
{
	glLightfv(GL_LIGHT0, GL_SPECULAR, m_vSpecular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, m_vAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, m_vDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, m_fpPosition);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}



void LightState::disable()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}
