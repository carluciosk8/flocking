/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Boid.h"
#include "../Engine/Math/Math.h"
#include "../Engine/Math/transform.h"

#include <cassert>
#include <iostream>

using std::cout;
using std::endl;


//
// Init static members
list<Boid*>  Boid::m_BoidsList(0);
LeaderBoid*  Boid::m_opLeaderBoid = NULL;
Terrain*  Boid::s_opTerrain = NULL;

float3  Boid::s_vFlockCenter(float3::ZERO);
float3  Boid::s_vFlockVelocity(float3::ZERO);
float  Boid::s_Ks  = 125.0f;
float  Boid::s_Ka  = 25.0f;
float  Boid::s_Kc  = 25.0f;
float  Boid::s_Kg  = 12.5f;
float  Boid::s_DKs = 0.0f;
float  Boid::s_DKa = 0.0f;
float  Boid::s_DKc = 0.0f;
float  Boid::s_DKg = 0.0f;



Boid::Boid(const char* cpName)
:
    SimulationObject(cpName),
    m_opNearestBoid(NULL),
    m_fNearestBoidDistanceSqr(999999999.9f)
{
    printf("Creating Boid: %s\n", cpName);

	m_BoidsList.push_back(this);

	MaxSpeed = newRand(10.0f, 15.0f);
	MaxSpeedSqr = MaxSpeed*MaxSpeed;
	MaxChange = (MaxSpeed*0.1f);
	MaxChangeSqr = MaxChange*MaxChange;
    m_fPerceptionRadiusSqr = newRand(16.0f,64.0f);
}



Boid::Boid(const char* cpName, const float3& vfPos, const float3& vfVel)
:
    SimulationObject(cpName, vfPos, vfVel),
    m_opNearestBoid(NULL),
    m_fNearestBoidDistanceSqr(999999999.9f)
{
    printf("Creating Boid: %s\n", cpName);

	m_BoidsList.push_back(this);

    MaxSpeed = newRand(10.0f, 15.0f);
	MaxSpeedSqr = MaxSpeed*MaxSpeed;
	MaxChange = (MaxSpeed*0.1f);
	MaxChangeSqr = MaxChange*MaxChange;
    m_fPerceptionRadiusSqr = newRand(16.0f,64.0f);
}



Boid::~Boid()
{
    list<Boid*>::iterator i = m_BoidsList.begin();
    while (i != m_BoidsList.end())
    {
        if (*i == this)
        {
            m_BoidsList.erase(i);
            i = m_BoidsList.begin();
        }
        ++i;
    }
    printf("Deleting Boid: %s\n", m_sName.c_str());
}



void Boid::update(float dt)
{
	assert(m_opLeaderBoid);
	m_vAcc = float3::ZERO;

	// Determine if we can see any of our flockmates.
	seeBoids();

	// Flocking behavior.
	if (m_BoidsSeenList.size())
	{
		// Implement Rule #1 (Separation).
		// Try to maintain our desired separation distance from our nearest flockmate.
		accumulateSeparationInfluence();

		// Implement Rule #2 (Alignment).
		// Try to move the same way our nearest flockmate does.
		accumulateAlignmentInfluence();

		// Implement Rule #3 (Cohesion).
		// Try to move towards the center of the flock.
		accumulateCohesionInfluence();
	}

    // Try to move towards the goal boid
    accumulateGoalInfluence();

    // Avoid ground
    avoidGround();

    //Avoid Tower
    avoidTower();

    // Scale acceleration by the frame duration to get independence of frame-rate changes
	m_vAcc *= dt;

	// Constrain acceleration
	// If our acceleration change is more than we allow, constrain it
	if (m_vAcc.norm2() > MaxChangeSqr)
	{
	   m_vAcc.normalize();
	   m_vAcc *= MaxChange;
	}

	// Update Velocity;
	m_vOldVelocity = m_vfVelocity;     // save off our previous velocity
	m_vfVelocity += m_vAcc;

	// Constrain speed.
	if ((m_fSpeedSqr = m_vfVelocity.norm2()) > MaxSpeedSqr)
	{
		m_vfVelocity.normalize();
		m_vfVelocity *= MaxSpeed;
		m_fSpeedSqr = MaxSpeedSqr;
	}

	// Update our position.
	m_vOldPosition = m_vfTranslate;
	SimulationObject::update(dt);

	// Compute roll/pitch/yaw.
	updateOrientation();

    // Cheat
    if ( m_vfTranslate.y < 10.0f + s_opTerrain->getHeight(m_vfTranslate.x, m_vfTranslate.z) )
        m_vfTranslate.y = 10.0f + s_opTerrain->getHeight(m_vfTranslate.x, m_vfTranslate.z);
}



void Boid::seeBoids()
{
    float3 v;
    float d2;

    m_BoidsSeenList.clear();
    for (list<Boid*>::iterator  i = m_BoidsList.begin() ; i != m_BoidsList.end() ; ++i)
    {
        v.sub( (*i)->getTranslate() , getTranslate() );
        d2 = v.norm2();
        if ( d2 < m_fPerceptionRadiusSqr )
        {
            m_BoidsSeenList.push_back(*i);
            if ( d2 < m_fNearestBoidDistanceSqr )
            {
                m_fNearestBoidDistanceSqr = d2;
                m_opNearestBoid = *i;
            }
        }
    }
}



void Boid::accumulateSeparationInfluence()
{
    if (m_BoidsSeenList.size() > 0)
    {
		float3 center;
		float3 change;


		// walk down the visibility list and sum up their position vectors
		for (list<Boid*>::iterator  i = m_BoidsSeenList.begin() ; i != m_BoidsSeenList.end() ; ++i)
			center += (*i)->getTranslate();

		// average the positions to get the perceived center of the flock
		center /= float(m_BoidsSeenList.size());

		// compute vector towards center of the flock
		change.sub(center, getTranslate()); 
		float d2 = change.norm2();

		if (d2 > 0)
		{
			change.normalize();
			change *= -s_Ks/d2;

			// accumulate change vector
			m_vAcc += change;
		}
	}
}



void Boid::accumulateAlignmentInfluence()
{
    if (m_BoidsSeenList.size() > 0)
    {
		assert(m_opNearestBoid);

		// copy the heading of our nearest buddy
		float3 change = float3::ZERO;

		// walk down the visibility list and sum up their position vectors
		for (list<Boid*>::iterator  i = m_BoidsSeenList.begin() ; i != m_BoidsSeenList.end() ; ++i)
			change += (*i)->getVelocity();

		if (change.norm2() > 0)
		{
			// normalize and then scale our vector change a bit...after
			// all we can't instantly snap to a new heading.
			change.normalize();
			change *= s_Ka;

			// return change vector
			m_vAcc += change;
		}
	}
}



void Boid::accumulateCohesionInfluence()
{
    if (m_BoidsSeenList.size() > 0)
    {
        float3 center;
        float3 change;

        // walk down the visibility list and sum up their position vectors
        for (list<Boid*>::iterator  i = m_BoidsSeenList.begin() ; i != m_BoidsSeenList.end() ; ++i)
            center += (*i)->getTranslate();

        // average the positions to get the perceived center of the flock
        center /= float(m_BoidsSeenList.size());

        // now that we have the perceived center, computer a vector towards it
        change.sub(center , getTranslate());

        if (change.norm2() > 0)
        {
            // Scale the change vector so we don't turn on a dime..
            change.normalize();
            change *= s_Kc;

            // return change vector
            m_vAcc += change;
        }
    }
}



//void Boid::accumulateCruisingInfluence()
//{
//   float3  change = getVelocity();
//
//   float  diff = (change.norm() - DesiredSpeed)/ MaxSpeed;
//   float  urgency = (float) fabs(diff);
//
//
//   // constrain the urgency level
//   if (urgency < MinUrgency) urgency = MinUrgency;
//   if (urgency > MaxUrgency) urgency = MaxUrgency;
//
//   // Now add some "jitter" so that each boid has a 
//   // bit of randomness just to keep things interesting.
//   float jitter = newRand();
//
//   if (jitter < 0.45f)
//      change.x += MinUrgency * (diff/fabsf(diff));
//   else if (jitter < 0.90f)
//      change.z += MinUrgency * (diff/fabsf(diff));
//   else
//      change.y += MinUrgency * (diff/fabsf(diff));   // we don't like vertical motion all that much
//
//
//   // compute velocity change necessary to get to our desired cruising speed
//   //change.SetMagnitudeOfVector ((urgency * (diff > 0 ? -1 : 1) ));
//   change.normalize();
//   change *= (urgency * (diff > 0 ? -1 : 1) );
//
//   m_vAcc += change;
//}



void Boid::accumulateGoalInfluence()
{
    float3 change;

    // computer a vector towards goal
    change = m_opLeaderBoid->getTranslate() - getTranslate();

    // Scale the change vector so we don't turn on a dime..
    change.normalize();
    change *= s_Kg;

    // return change vector
    m_vAcc += change;
}



void Boid::avoidGround()
{
    assert(s_opTerrain);

    float3 forward = m_vfVelocity;
    forward.normalize();
    forward = getTranslate() + forward*10.0f;

    float fBoidHeight1 = (getTranslate().y - s_opTerrain->getHeight(getTranslate().x, getTranslate().z));
    float fBoidHeight2 = (forward.y - s_opTerrain->getHeight(forward.x, forward.z));

    if ( fBoidHeight1 < 0.0f )
        fBoidHeight1 = 0.000001f;
    if ( fBoidHeight2 < 0.0f )
        fBoidHeight2 = 0.000001f;

    float3 change;
    change = s_opTerrain->getNormal(getTranslate().x, getTranslate().z);
    change *= 1000.0f/(fBoidHeight1*fBoidHeight1);
    m_vAcc += change;
    change = s_opTerrain->getNormal(forward.x, forward.z);
    change *= 1000.0f/(fBoidHeight2*fBoidHeight2);
    m_vAcc += change;
}



void Boid::avoidTower()
{
    float fPosX = 0.0f;
    float fPosZ = 0.0f;
    float fPosY = s_opTerrain->getHeight(fPosX, fPosZ);
    float fRadSqr = 100.0f;
    float fHeight = 50.0f;

    if ( (getTranslate().y > fPosY) && (getTranslate().y < (fPosY + fHeight)) )
    {
        float fDistSqr = (getTranslate().x * getTranslate().x) + (getTranslate().z * getTranslate().z) - fRadSqr;
        if ( fDistSqr < 0.0f )
            fDistSqr = 0.000001f;
        //{
            float3 change(getTranslate().x, 0, getTranslate().z);
            change.normalize();
            change *= 100.0f/fDistSqr;
            m_vAcc += change;
        //}
    }
}



void Boid::updateOrientation()
{
    float roll=0.0f;
    float pitch=0.0f;
    float yaw=0.0f;

    // Determine the direction of the lateral acceleration.
    float3 forward = m_vfVelocity;
    float3 lateral = m_vOldVelocity;
    float3 tmp;

    // compute roll
	if (lateral.norm2()>0.0f)
    {
        forward.normalize();
        lateral.normalize();
		tmp.cross(forward, lateral);
    
		if (tmp.y>0)
			roll = acosf(forward.dot(lateral))*25.0f;
		else
			roll = -acosf(forward.dot(lateral))*25.0f;
    }
    else
        roll = 0.0f;

    // compute pitch
    pitch = -M_PI/2-atanf(m_vfVelocity.y / sqrtf((m_vfVelocity.z*m_vfVelocity.z) + (m_vfVelocity.x*m_vfVelocity.x)));

    // compute yaw
    yaw = atan2f(m_vfVelocity.x, m_vfVelocity.z);

	// set rotate matrix of the boid to math the desired orientation
    rotateYXZ(m_mfRotate, yaw, pitch, roll);
}



void Boid::calcFlockCenter()
{
	s_vFlockCenter = float3::ZERO;
	s_vFlockVelocity = float3::ZERO;

    for (list<Boid*>::iterator  i = m_BoidsList.begin() ; i != m_BoidsList.end() ; ++i)
	{
		s_vFlockCenter += (*i)->getTranslate();
		s_vFlockVelocity += (*i)->getVelocity();
	}

	s_vFlockCenter /= float(m_BoidsList.size());
	s_vFlockVelocity.normalize();
}
