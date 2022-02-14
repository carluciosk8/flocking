/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __SCENEOBJECT_H__
#define __SCENEOBJECT_H__


#include <string>
#include <list>
#include <vector>

using std::string;
using std::list;
using std::vector;

#include "../Math/Vector3.h"
#include "../Math/Matrix3.h"
#include "../Math/Matrix4.h"
#include "Sphere.h"


class RenderState;
class RenderableObject;

class SceneObject// : public RenderableObject
{
    public:
        SceneObject(const char* cpName);
        virtual ~SceneObject();

        inline const float getScale() const { return m_fScale; }
        inline const float3x3& getRotate() const { return m_mfRotate; }
        inline const float3& getTranslate() const { return m_vfTranslate; }

        inline void setScale(float fScale) { m_fScale = fScale; }
        inline void setRotate(const float3x3& mfRotate) { m_mfRotate = mfRotate; }
        inline void setTranslate(const float3& vfTranslate) { m_vfTranslate = vfTranslate; }
        inline void setTranslate(float x, float y, float z) { m_vfTranslate.set(x, y, z); }

        void addRenderState(RenderState* opState);
        void removeRenderState(const RenderState* opState);

        void addObject(RenderableObject* opObject);
        void removeObject(const RenderableObject* opObject);

        void addChild(SceneObject* opChild);
        void removeChild(const SceneObject* opChild);

        RenderableObject* getObject();

        virtual void update(float dt);
        void draw();


    protected:
        // Name
	    string  m_sName;

        float  m_fScale;
        float3x3  m_mfRotate;
        float3  m_vfTranslate;

        // Local Transforms
        float  m_fLocalScale;
        float3x3  m_mLocalRotate;
        float3  m_vLocalTranslate;

        // World Transforms
        float  m_fWorldScale;
        float3x3  m_mWorldRotate;
        float3  m_vWorldTranslate;

        float4x4  m_mfGLmodelview;

        Sphere  m_oBoundSphere;

        list<RenderState*>  m_RenderStateList;
        list<RenderableObject*>  m_ObjectList;
        vector<SceneObject*>  m_Children;
};


#endif
