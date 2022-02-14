/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __SIMULATIONOBJECT_H__
#define __SIMULATIONOBJECT_H__


#include "SceneObject.h"
#include "../Math/Vector3.h"


class SimulationObject : public SceneObject
{
	public:
	    SimulationObject(const char* cpName);
	    SimulationObject(const char* cpName, const float3& vfPos, const float3& vfVel);
	    virtual ~SimulationObject();

        inline const float3& getVelocity()  { return m_vfVelocity; }

        virtual void update(float dt);


	protected:
        float3  m_vfVelocity;
};


#endif
