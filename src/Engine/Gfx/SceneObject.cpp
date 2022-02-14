/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "SceneObject.h"
#include "RenderState.h"
#include "RenderableObject.h"

#include <GL/glew.h>

#include <algorithm>
#include <cstdio>


SceneObject::SceneObject(const char* cpName)
: m_sName(cpName),
  m_fScale(1),
  m_mfRotate(float3x3::IDENTITY),
  m_vfTranslate(float3::ZERO),
  m_mfGLmodelview(float4x4::IDENTITY)
{
    printf("Creating SceneObject: %s\n", m_sName.c_str());
}



SceneObject::~SceneObject()
{
    printf("Deleting SceneObject: %s\n", m_sName.c_str());
    for (list<RenderState*>::iterator  i = m_RenderStateList.begin() ;
         i != m_RenderStateList.end() ;
         ++i)
        delete *i;
}



void SceneObject::addRenderState(RenderState* opState)
{
    if (opState)
        m_RenderStateList.push_back(opState);
}



void SceneObject::removeRenderState(const RenderState* opState)
{
    m_RenderStateList.erase( std::remove(m_RenderStateList.begin(), m_RenderStateList.end(), opState),
                             m_RenderStateList.end() );
}



void SceneObject::addObject(RenderableObject* opObject)
{
    if (opObject)
        m_ObjectList.push_back(opObject);
}



void SceneObject::removeObject(const RenderableObject* opObject)
{
    m_ObjectList.erase( std::remove(m_ObjectList.begin(), m_ObjectList.end(), opObject),
                        m_ObjectList.end() );
}



void SceneObject::addChild(SceneObject* opChild)
{
    if (opChild)
        m_Children.push_back(opChild);
}



void SceneObject::removeChild(const SceneObject* opChild)
{
    m_Children.erase( std::remove(m_Children.begin(), m_Children.end(), opChild),
                      m_Children.end() );
}



RenderableObject* SceneObject::getObject()
{
    return m_ObjectList.back();
}



void SceneObject::update(float dt)
{
    m_mfGLmodelview.set
    (
        m_fScale*m_mfRotate.m[0][0] , m_fScale*m_mfRotate.m[1][0] , m_fScale*m_mfRotate.m[2][0] , 0.0f,
        m_fScale*m_mfRotate.m[0][1] , m_fScale*m_mfRotate.m[1][1] , m_fScale*m_mfRotate.m[2][1] , 0.0f,
        m_fScale*m_mfRotate.m[0][2] , m_fScale*m_mfRotate.m[1][2] , m_fScale*m_mfRotate.m[2][2] , 0.0f,
                 m_vfTranslate.x    ,          m_vfTranslate.y    ,          m_vfTranslate.z    , 1.0f
    );
}



void SceneObject::draw()
{
    glPushMatrix();
    glMultMatrixf((float*)m_mfGLmodelview.m);
    for (list<RenderState*>::iterator i=m_RenderStateList.begin() ;
         i != m_RenderStateList.end() ;
         ++i)
        (*i)->enable();

    for (list<RenderableObject*>::iterator i=m_ObjectList.begin() ;
         i != m_ObjectList.end() ;
         ++i)
        (*i)->render();

    glPopMatrix();
    for (list<RenderState*>::iterator i=m_RenderStateList.begin() ;
         i != m_RenderStateList.end() ;
         ++i)
        (*i)->disable();
}
