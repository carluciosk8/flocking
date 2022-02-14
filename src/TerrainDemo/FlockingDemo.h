/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __FLOCKINGDEMO_H__
#define __FLOCKINGDEMO_H__


#define  SCREEN_WIDTH   1024
#define  SCREEN_HEIGHT  768


#include "../Engine/Core/Application.h"
#include "../Engine/Gfx/Scene.h"
#include "../Engine/Gfx/Viewport.h"
#include "../Engine/Gfx/TextBox.h"
#include "../Engine/Gfx/SceneObject.h"
#include "../Engine/Gfx/Terrain.h"
#include "../Engine/Gfx/Md2.h"

#include "LeaderBoid.h"


class FlockingDemo : public Application
{
    public:
        FlockingDemo();
        virtual ~FlockingDemo();


        virtual void init();
        virtual void shutdown();


    protected:
        virtual void handleEvents();
        virtual void update();
        virtual void draw();

        void drawInfoText();
        void drawHelpText();

        void addBoid();
        void remBoid();


    protected:
        Viewport*  m_opViewport;
        Scene  m_oScene;

        SceneObject  m_oTerrain;
        SceneObject  m_oTower;
        LeaderBoid  m_oLeaderBoid;
        Camera*  m_opTowerCamera;
        Camera*  m_opFlockBehindCamera;
        Camera*  m_opFlockSideCamera;

        Terrain  m_oTerrainModel;
		CMd2*  m_opLeaderBoidModel;

        TextBox*  m_opInfoText;
		TextBox*  m_opDebugText;
		TextBox*  m_opHelpText;
};


#endif
