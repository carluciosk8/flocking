/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __SCENE_H__
#define __SCENE_H__


#include <list>

using std::list;


class SceneObject;
class RenderState;

class Scene
{
    public:
        Scene();
        ~Scene();

        void update(float dt);
        void draw();

        void addRenderState(RenderState* opState);
        void removeRenderState(const RenderState* opState);
		void enableGlobalStates();
		void disableGlobalStates();
        void addObject(SceneObject* opObject);
        void remObject(const SceneObject* opObject);


    protected:
        list<SceneObject*>  m_ObjectList;
        list<RenderState*>  m_RenderStateList;
};


#endif
