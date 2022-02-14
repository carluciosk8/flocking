/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Scene.h"
#include "SceneObject.h"
#include "RenderState.h"

#include <algorithm>


Scene::Scene()
{
}



Scene::~Scene()
{
}



void Scene::update(float dt)
{
    for (list<SceneObject*>::iterator i=m_ObjectList.begin() ; i != m_ObjectList.end() ; ++i)
        (*i)->update(dt);
}



void Scene::draw()
{
    for (list<RenderState*>::iterator i=m_RenderStateList.begin() ; i != m_RenderStateList.end() ; ++i)
        (*i)->enable();

    for (list<SceneObject*>::iterator i=m_ObjectList.begin() ; i != m_ObjectList.end() ; ++i)
        (*i)->draw();

    for (list<RenderState*>::iterator i=m_RenderStateList.begin() ; i != m_RenderStateList.end() ; ++i)
        (*i)->disable();
}



void Scene::addRenderState(RenderState* opState)
{
	if (opState)
		m_RenderStateList.push_back(opState);
}



void Scene::removeRenderState(const RenderState* opState)
{
    m_RenderStateList.erase( std::remove(m_RenderStateList.begin(), m_RenderStateList.end(), opState),
                             m_RenderStateList.end() );
}



void Scene::enableGlobalStates()
{
    for (list<RenderState*>::iterator i=m_RenderStateList.begin() ; i != m_RenderStateList.end() ; ++i)
        (*i)->enable();
}


		
void Scene::disableGlobalStates()
{
    for (list<RenderState*>::iterator i=m_RenderStateList.begin() ; i != m_RenderStateList.end() ; ++i)
        (*i)->disable();
}



void Scene::addObject(SceneObject* opObject)
{
	if (opObject)
		m_ObjectList.push_back(opObject);
}



void Scene::remObject(const SceneObject* opObject)
{
    m_ObjectList.erase( std::remove(m_ObjectList.begin(), m_ObjectList.end(), opObject), m_ObjectList.end() );
}
