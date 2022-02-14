/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "LeaderBoid.h"
#include "../Engine/Math/transform.h"
#include "../Engine/Math/Math.h"

#include <cstdio>

#define  MAX_LEADER_SPEED    15.0
#define  MIN_LEADER_SPEED     5.0
#define  MAX_LEADER_PITCH    0.45 * M_PI
#define  MIN_LEADER_PITCH   -0.45 * M_PI


LeaderBoid::LeaderBoid(const char* cpName)
:
    SimulationObject(cpName),
    m_fVel(0.0f),
    m_fAcc(0.0f),
    m_fYaw(0.0f),
    m_fPitch(0.0f),
    m_fVelYaw(0.0f),
    m_fVelPitch(0.0f),
    m_oCamera(20.0f, 100.0f/600.0f, 0.5f, 100.0f)
{
    printf("Creating LeaderBoid: %s\n", cpName);
}



LeaderBoid::LeaderBoid(const char* cpName, const float3& vfPos, const float3& vfVel)
:
    SimulationObject(cpName, vfPos, vfVel),
    m_fVel(0.0f),
    m_fAcc(0.0f),
    m_fYaw(0.0f),
    m_fPitch(0.0f),
    m_fVelYaw(0.0f),
    m_fVelPitch(0.0f),
    m_oCamera(20.0f, 100.0f/600.0f, 0.5f, 200.0f)
{
    printf("Creating LeaderBoid: %s\n", cpName);
}



LeaderBoid::~LeaderBoid()
{
    printf("Deleting LeaderBoid: %s\n", m_sName.c_str());
}



void LeaderBoid::update(float dt)
{
    m_fPitch += m_fVelPitch * dt;
    m_fYaw += m_fVelYaw * dt;
    m_fVel += m_fVel * m_fAcc * dt;

    if (m_fPitch > MAX_LEADER_PITCH)
        m_fPitch = MAX_LEADER_PITCH;
    else if (m_fPitch < MIN_LEADER_PITCH)
        m_fPitch = MIN_LEADER_PITCH;

    if (m_fYaw >= 2*M_PI)
        m_fYaw = 0.0f;
    else if (m_fYaw < 0.0f)
        m_fYaw = 2*M_PI;

    if (m_fVel > MAX_LEADER_SPEED)
        m_fVel = MAX_LEADER_SPEED;
    else if (m_fVel < MIN_LEADER_SPEED)
        m_fVel = MIN_LEADER_SPEED;

    float3x3  mRX;
    float3x3  mRY;
    rotateZ(mRX, m_fPitch);
    rotateY(mRY, m_fYaw);
    m_mfRotate.mul(mRY, mRX);

    m_vfVelocity.set(m_mfRotate.m[0][0], m_mfRotate.m[1][0], m_mfRotate.m[2][0]);
    m_vfVelocity = m_vfVelocity * m_fVel;

    float3 vDist(m_mfRotate.m[0][0], m_mfRotate.m[1][0], m_mfRotate.m[2][0]);
    m_oCamera.setPosition(m_vfTranslate - vDist*15.0f - m_vfVelocity*0.1f + float3::UNIT_Y);
    m_oCamera.setForward(m_vfVelocity);

    updateOrientation();
    SimulationObject::update(dt);
}



void LeaderBoid::updateOrientation()
{
    float roll=0.0f;
    float pitch=0.0f;
    float yaw=0.0f;

    // Determine the direction of the lateral acceleration.
    float3 forward = m_vfVelocity;
    float3 lateral = float3::ZERO;// m_vOldVelocity;
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
