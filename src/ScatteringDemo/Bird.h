/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __FLYINGCAMERA_H__
#define __FLYINGCAMERA_H__


#include "../Engine/Gfx/SimulationObject.h"
#include "../Engine/Gfx/Camera.h"


class FlyingCamera : public SimulationObject
{
    public:
        FlyingCamera(const char* cpName);
        FlyingCamera(const char* cpName, const float3& vfPos, const float3& vfVel);
        virtual ~FlyingCamera();

        virtual void update(float dt);

        inline void setVelPitch(float fVelPitch)  { m_fVelPitch = fVelPitch; }
        inline void setVelYaw(float fVelYaw)  { m_fVelYaw = fVelYaw; }
        inline void setAcc(float fAcc)  { m_fAcc = fAcc; }

        inline Camera& getCamera()  { return m_oCamera; }


    protected:
        void updateOrientation();


        float  m_fVel;
        float  m_fAcc;
        float  m_fYaw;
        float  m_fPitch;
        float  m_fVelYaw;
        float  m_fVelPitch;

        Camera  m_oCamera;
};


#endif
