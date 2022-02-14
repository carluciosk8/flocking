/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __CAMERA_H__
#define __CAMERA_H__


#include "../Math/Vector3.h"
#include "../Math/Matrix4.h"


class Camera
{
    public:
        Camera(float fFoV, float fAspect, float fNear, float fFar);
        ~Camera();

        inline void lookAt(const float3& vLookAtPoint) { m_f3Forward =  vLookAtPoint - m_f3Position; }

        inline void setPosition(const float3& f3Pos) { m_f3Position = f3Pos; }
        inline void setForward(const float3& f3For) { m_f3Forward = f3For; }
        inline void setUp(const float3& f3Up) { m_f3Up = f3Up; }

        inline const float3& getPosition() const { return m_f3Position; }
        inline const float3& getForward() const { return m_f3Forward; }
        inline const float3& getUp() const { return m_f3Up; }
        inline const float4x4& getView() const { return m_mView; }

        void updateProjection();
        void updateView();


    protected:
        float  m_fFieldOfView;
        float  m_fAspect;
        float  m_fNear;
        float  m_fFar;

        float3  m_f3Position;
        float3  m_f3Forward;
        float3  m_f3Up;

        float4x4  m_mView;
};


#endif
