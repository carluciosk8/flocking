/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "FogState.h"

#include <GL/glew.h>


FogState::FogState(float fStart, float fEnd, float fDensity, const float4& vrColor)
: m_iMode(GL_EXP),
  m_fDensity(fDensity),
  m_fStart(fStart),
  m_fEnd(fEnd),
  m_vColor(vrColor)
{
}



FogState::~FogState()
{
}



void FogState::enable()
{
    glEnable(GL_FOG);
    glFogi(GL_FOG_MODE, m_iMode);
    glFogfv(GL_FOG_COLOR, &m_vColor.x);
    glFogf(GL_FOG_DENSITY, m_fDensity);
    glHint(GL_FOG_HINT, GL_DONT_CARE);
    glFogf(GL_FOG_START, m_fEnd);
    glFogf(GL_FOG_END, m_fEnd);
}



void FogState::disable()
{
}
