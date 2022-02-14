/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Application.h"
#include "../Gfx/Screen.h"
#include "../Gfx/Scene.h"
#include "../Gfx/Camera.h"

#ifdef _WIN32
#include "TimeSourceHRWin32.h"
#else
#include "TimeSourceHRLinux.h"
#endif

#include <cassert>
#include <SDL/SDL.h>


Application::Application()
:
    m_bIsRunning(true),
    m_opScreen(NULL),
    m_opActiveCamera(NULL),
	m_opActiveScene(NULL),
	m_oClock(),
	m_oTimer(m_oClock)
{
    #ifdef _WIN32
    m_oClock.SetTimeSource(new TimeSourceHRWin32);
    #else
    m_oClock.SetTimeSource(new TimeSourceHRLinux);
    #endif
}



Application::~Application()
{
    for (uint i=0 ; i<m_oEventKeyDownHandlerList.size() ; ++i)
        delete m_oEventKeyDownHandlerList[i];
    for (uint i=0 ; i<m_oEventKeyUpHandlerList.size() ; ++i)
        delete m_oEventKeyDownHandlerList[i];
}



void Application::run()
{
    while (m_bIsRunning)
    {
        handleEvents();
        update();
        draw();
    }
}



void Application::handleEvents()
{
    SDL_Event event;


    while( SDL_PollEvent( &event ) )
    {
        switch( event.type )
        {
            case SDL_KEYDOWN:
            {
                for (uint i=0 ; i<m_oEventKeyDownHandlerList.size() ; ++i)
                    if (m_oEventKeyDownHandlerList[i]->getType() == event.key.keysym.sym)
                        m_oEventKeyDownHandlerList[i]->doIt();
            }
            break;

            case SDL_KEYUP:
            {
                for (uint i=0 ; i<m_oEventKeyUpHandlerList.size() ; ++i)
                    if (m_oEventKeyUpHandlerList[i]->getType() == event.key.keysym.sym)
                        m_oEventKeyUpHandlerList[i]->doIt();
            }
            break;

            case SDL_QUIT:
                m_bIsRunning = false;
                break;
        }
    }
}



void Application::update()
{
	assert(m_opActiveScene);
    m_oClock.FrameStep();
    m_opActiveScene->update( float(m_oTimer.getFrameDuration()) );
}



void Application::draw()
{
	assert(m_opActiveScene && m_opActiveCamera && m_opScreen);

    //m_opScreen->beginRender();

    m_opActiveCamera->updateView();
    m_opActiveScene->draw();

    //m_opScreen->endRender();
}



void Application::setActiveScene(Scene* opScene)
{
	assert(opScene);
	m_opActiveScene = opScene;
}



void Application::setActiveCamera(Camera* opCamera)
{
	assert(opCamera);
	m_opActiveCamera = opCamera;
}


void Application::registerKeyDownEvent(EventHandler* ev)
{
    m_oEventKeyDownHandlerList.push_back(ev);
}


void Application::registerKeyUpEvent(EventHandler* ev)
{
    m_oEventKeyUpHandlerList.push_back(ev);
}
