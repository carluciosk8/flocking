/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Camera.h"

#include <GL/glew.h>


Camera::Camera(float fFoV, float fAspect, float fNear, float fFar)
: m_fFieldOfView(fFoV),
  m_fAspect(fAspect),
  m_fNear(fNear),
  m_fFar(fFar),
  m_f3Position(float3::ZERO),
  m_f3Forward(-float3::UNIT_Z),
  m_f3Up(float3::UNIT_Y)
{
    updateProjection();
    updateView();
}



Camera::~Camera()
{
}



void Camera::updateProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(m_fFieldOfView, m_fAspect, m_fNear, m_fFar);
    glMatrixMode(GL_MODELVIEW);
}



void Camera::updateView()
{
	glLoadIdentity();
    gluLookAt(m_f3Position.x, m_f3Position.y, m_f3Position.z,
              m_f3Position.x + m_f3Forward.x, m_f3Position.y + m_f3Forward.y, m_f3Position.z + m_f3Forward.z,
              m_f3Up.x, m_f3Up.y, m_f3Up.z);
    glGetFloatv(GL_MODELVIEW_MATRIX, &(m_mView.m[0][0]));
}
