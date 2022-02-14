/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Bird.h"
#include "../Engine/Math/transform.h"
#include "../Engine/Math/Math.h"

#include <cstdio>

#define  MAX_SPEED    150.0
#define  MIN_SPEED     0.1
#define  MAX_PITCH    0.45 * M_PI
#define  MIN_PITCH   -0.45 * M_PI

#define  SCREEN_WIDTH   1024
#define  SCREEN_HEIGHT  768

FlyingCamera::FlyingCamera(const char* cpName)
:
    SimulationObject(cpName),
    m_fVel(0.0f),
    m_fAcc(0.0f),
    m_fYaw(0.0f),
    m_fPitch(0.0f),
    m_fVelYaw(0.0f),
    m_fVelPitch(0.0f),
    m_oCamera(60.0f, float(SCREEN_WIDTH)/SCREEN_HEIGHT, 0.5f, 350000.0f)
{
    printf("Creating FlyingCamera: %s\n", cpName);
}



FlyingCamera::FlyingCamera(const char* cpName, const float3& vfPos, const float3& vfVel)
:
    SimulationObject(cpName, vfPos, vfVel),
    m_fVel(0.0f),
    m_fAcc(0.0f),
    m_fYaw(0.0f),
    m_fPitch(0.0f),
    m_fVelYaw(0.0f),
    m_fVelPitch(0.0f),
    m_oCamera(60.0f, float(SCREEN_WIDTH)/SCREEN_HEIGHT, 0.5f, 350000.0f)
{
    printf("Creating FlyingCamera: %s\n", cpName);
}



FlyingCamera::~FlyingCamera()
{
    printf("Deleting FlyingCamera: %s\n", m_sName.c_str());
}



void FlyingCamera::update(float dt)
{
    m_fPitch += m_fVelPitch * dt;
    m_fYaw += m_fVelYaw * dt;
    m_fVel += m_fAcc * dt;

    if (m_fPitch > MAX_PITCH)
        m_fPitch = MAX_PITCH;
    else if (m_fPitch < MIN_PITCH)
        m_fPitch = MIN_PITCH;

    if (m_fYaw >= 2*M_PI)
        m_fYaw = 0.0f;
    else if (m_fYaw < 0.0f)
        m_fYaw = 2*M_PI;

    if (m_fVel > MAX_SPEED)
        m_fVel = MAX_SPEED;
    else if (m_fVel < MIN_SPEED)
        m_fVel = MIN_SPEED;

    float3x3  mRX;
    float3x3  mRY;
    rotateZ(mRX, m_fPitch);
    rotateY(mRY, m_fYaw);
    m_mfRotate.mul(mRY, mRX);

	m_vfVelocity.set(m_mfRotate.m[0][0], m_mfRotate.m[1][0], m_mfRotate.m[2][0]);
    m_vfVelocity = m_vfVelocity * m_fVel;

    float3 vDist(m_mfRotate.m[0][0], m_mfRotate.m[1][0], m_mfRotate.m[2][0]);
    m_oCamera.setPosition(m_vfTranslate);
    m_oCamera.setForward(m_vfVelocity);

    SimulationObject::update(dt);
}
