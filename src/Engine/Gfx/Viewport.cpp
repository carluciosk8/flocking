/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Viewport.h"

#include <GL/glew.h>


Viewport::Viewport(int iX, int iY, int iWidth, int iHeight)
: m_iX(iX),
  m_iY(iY),
  m_iWidth(iWidth),
  m_iHeight(iHeight)
{
}



Viewport::~Viewport()
{
}



void Viewport::setViewport()
{
    glViewport(m_iX, m_iY, m_iWidth, m_iHeight);
}
