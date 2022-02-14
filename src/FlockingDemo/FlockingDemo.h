/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __FLOCKINGDEMO_H__
#define __FLOCKINGDEMO_H__


#include "../Engine/Core/Application.h"
#include "../Engine/Gfx/Scene.h"
#include "../Engine/Gfx/Viewport.h"
#include "../Engine/Gfx/TextBox.h"
#include "../Engine/Gfx/SceneObject.h"
#include "../Engine/Gfx/Terrain.h"
#include "../Engine/Gfx/Md2.h"
#include "../Engine/Gfx/ShaderState.h"

#include "LeaderBoid.h"
#include "Atmosphere.h"
#include "Sky.h"
#include "Sun.h"


#define  SCREEN_WIDTH   720
#define  SCREEN_HEIGHT  480


class FlockingDemo : public Application
{
    public:
        FlockingDemo(int iWidth, int iHeight);
        virtual ~FlockingDemo();


        virtual void init();
        virtual void shutdown();

        DECLARE_CALLBACK(onPressUp);
        DECLARE_CALLBACK(onPressDown);
        DECLARE_CALLBACK(onPressLeft);
        DECLARE_CALLBACK(onPressRight);
        DECLARE_CALLBACK(onPressAccel);
        DECLARE_CALLBACK(onPressDecel);
        DECLARE_CALLBACK(onPressAccel2);
        DECLARE_CALLBACK(onPressDecel2);
        DECLARE_CALLBACK(onPressIncDKs);
        DECLARE_CALLBACK(onPressDecDKs);
        DECLARE_CALLBACK(onPressIncDKa);
        DECLARE_CALLBACK(onPressDecDKa);
        DECLARE_CALLBACK(onPressIncDKc);
        DECLARE_CALLBACK(onPressDecDKc);
        DECLARE_CALLBACK(onPressIncDKg);
        DECLARE_CALLBACK(onPressDecDKg);

        DECLARE_CALLBACK(onReleaseUp);
        DECLARE_CALLBACK(onReleaseDown);
        DECLARE_CALLBACK(onReleaseLeft);
        DECLARE_CALLBACK(onReleaseRight);
        DECLARE_CALLBACK(onReleaseAccel);
        DECLARE_CALLBACK(onReleaseDecel);
        DECLARE_CALLBACK(onReleaseAccel2);
        DECLARE_CALLBACK(onReleaseDecel2);
        DECLARE_CALLBACK(onReleaseIncDKs);
        DECLARE_CALLBACK(onReleaseDecDKs);
        DECLARE_CALLBACK(onReleaseIncDKa);
        DECLARE_CALLBACK(onReleaseDecDKa);
        DECLARE_CALLBACK(onReleaseIncDKc);
        DECLARE_CALLBACK(onReleaseDecDKc);
        DECLARE_CALLBACK(onReleaseIncDKg);
        DECLARE_CALLBACK(onReleaseDecDKg);

        DECLARE_CALLBACK(onPressHelp);
        DECLARE_CALLBACK(onPressIncBoid);
        DECLARE_CALLBACK(onPressDecBoid);
        DECLARE_CALLBACK(onPressChangeCameraLeader);
        DECLARE_CALLBACK(onPressChangeCameraTower);
        DECLARE_CALLBACK(onPressChangeCameraBehind);
        DECLARE_CALLBACK(onPressChangeCameraSide);
        DECLARE_CALLBACK(onPressPause);
        DECLARE_CALLBACK(onPressQuit);


    protected:
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
        SceneObject  m_oSky;
        LeaderBoid  m_oLeaderBoid;

        Camera*  m_opTowerCamera;
        Camera*  m_opFlockBehindCamera;
        Camera*  m_opFlockSideCamera;

        Terrain  m_oTerrainModel;
        CMd2*  m_opLeaderBoidModel;
        Atmosphere  m_oAtm;
        Sun  m_oSun;
        Sky  m_oSkyModel;

        TextBox*  m_opInfoText;
        TextBox*  m_opHelpText;

        bool  m_bShowHelpText;
};


#endif
