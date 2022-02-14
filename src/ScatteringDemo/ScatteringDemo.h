/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __SCATTERINGDEMO_H__
#define __SCATTERINGDEMO_H__


#define  SCREEN_WIDTH   1024
#define  SCREEN_HEIGHT  768


#include "../Engine/Core/Application.h"
#include "../Engine/Gfx/Scene.h"
#include "../Engine/Gfx/Viewport.h"
#include "../Engine/Gfx/TextBox.h"
#include "../Engine/Gfx/SceneObject.h"
#include "../Engine/Gfx/Terrain.h"

#include "Sky.h"
#include "Bird.h"


class ScatteringDemo : public Application
{
    public:
        ScatteringDemo();
        virtual ~ScatteringDemo();


        virtual void init();
        virtual void shutdown();


    protected:
        virtual void handleEvents();
        virtual void update();
        virtual void draw();

        void drawInfoText();
        void drawHelpText();


    protected:
        Viewport*  m_opViewport;
        Scene  m_oScene;

        SceneObject  m_oTerrain;
        SceneObject  m_oSky;
        FlyingCamera  m_oFlyingCamera;

        Terrain  m_oTerrainModel;
        Sky  m_oSkyModel;

        TextBox*  m_opInfoText;
        TextBox*  m_opHelpText;
};


#endif
