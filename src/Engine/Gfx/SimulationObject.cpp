/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include <cstdio>
#include <cmath>


#include "SimulationObject.h"
#include "../Math/transform.h"


SimulationObject::SimulationObject(const char* cpName)
: SceneObject(cpName),
  m_vfVelocity(float3::UNIT_X)
{
    printf("Creating SimulationObject\n");
}  



SimulationObject::SimulationObject(const char* cpName, const float3& vfPos, const float3& vfVel)
: SceneObject(cpName),
  m_vfVelocity(vfVel)
{
    printf("Creating SimulationObject\n");
    this->setTranslate(vfPos);
}  



SimulationObject::~SimulationObject()
{
    printf("Deleting SimulationObject\n");
}



void SimulationObject::update(float dt)
{
    SceneObject::update(dt);
    m_vfTranslate += m_vfVelocity * dt;
}
