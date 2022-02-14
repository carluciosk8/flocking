/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include <cassert>
#include <SDL/SDL.h>

#include "../Engine/Math/Math.h"
#include "../Engine/Math/Vector3.h"
#include "../Engine/Math/Vector4.h"
#include "../Engine/Math/Matrix3.h"
#include "../Engine/Gfx/Screen.h"
#include "../Engine/Gfx/WireframeState.h"
#include "../Engine/Gfx/Texture.h"
#include "../Engine/Gfx/ShaderState.h"

#include "ScatteringDemo.h"


ScatteringDemo::ScatteringDemo()
:
    Application(),
    m_oTerrain("Terreno"),
    m_oSky("Ceu"),
    m_oFlyingCamera("Camera")
{
    m_opScreen = new Screen("Scattering Demo", SCREEN_WIDTH, SCREEN_HEIGHT, false);
    m_opViewport = new Viewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    m_opInfoText = new TextBox(10, SCREEN_WIDTH - 10, 10, 20);
    m_opHelpText = new TextBox(10, SCREEN_WIDTH - 10, 20, SCREEN_HEIGHT - 400);

    m_opInfoText->SetColor(TextBox::YELLOW);
    m_opHelpText->SetColor(TextBox::WHITE);
}



ScatteringDemo::~ScatteringDemo()
{
    delete m_opHelpText;
    delete m_opInfoText;
    delete m_opViewport;
    delete m_opScreen;
}



void ScatteringDemo::init()
{
    m_opViewport->setViewport();

    // Create Terrain
    m_oTerrainModel.generate(300, 60.0f);
    m_oTerrain.addObject(&m_oTerrainModel);
    m_oTerrain.addRenderState(new TextureState("resources/terrain.jpg"));
    m_oScene.addObject(&m_oTerrain);

    // Create Skydome
    m_oSkyModel.generate(8, 1000.0f);
    m_oSky.addObject(&m_oSkyModel);
    //m_oSky.addRenderState(new WireframeState());
    m_oSky.addRenderState(m_oSkyModel.getShader());
    m_oScene.addObject(&m_oSky);

    // Create Camera
    m_oFlyingCamera.setTranslate(0.0f, m_oTerrainModel.getHeight(0.0f, 0.0f) + 50.0f, 0.0f);
    m_oScene.addObject(&m_oFlyingCamera);
    m_oFlyingCamera.getCamera().updateProjection();

    // Set active scene
    m_opActiveCamera = &m_oFlyingCamera.getCamera();
    setActiveScene(&m_oScene);
}



void ScatteringDemo::shutdown()
{
}



void ScatteringDemo::handleEvents()
{
    SDL_Event event;


    while( SDL_PollEvent( &event ) )
    {
        switch( event.type )
        {
            case SDL_KEYDOWN:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        m_oFlyingCamera.setVelPitch(-0.5f);
                    }
                    break;

                    case SDLK_DOWN:
                    {
                        m_oFlyingCamera.setVelPitch(0.5f);
                    }
                    break;

                    case SDLK_LEFT:
                    {
                        m_oFlyingCamera.setVelYaw(0.5f);
                    }
                    break;

                    case SDLK_RIGHT:
                    {
                        m_oFlyingCamera.setVelYaw(-0.5f);
                    }
                    break;

                    case SDLK_a:
                    {
                        m_oFlyingCamera.setAcc(100.0f);
                    }
                    break;

                    case SDLK_ESCAPE:
                    {
                        m_bIsRunning = false;
                    }
                    break;

                    default:;
                }
            }
            break;

            case SDL_KEYUP:
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                    {
                        m_oFlyingCamera.setVelPitch(0.0f);
                    }
                    break;

                    case SDLK_DOWN:
                    {
                        m_oFlyingCamera.setVelPitch(0.0f);
                    }
                    break;

                    case SDLK_LEFT:
                    {
                        m_oFlyingCamera.setVelYaw(0.0f);
                    }
                    break;

                    case SDLK_RIGHT:
                    {
                        m_oFlyingCamera.setVelYaw(0.0f);
                    }
                    break;

                    case SDLK_a:
                    {
                        m_oFlyingCamera.setAcc(-100.0f);
                    }
                    break;

                    default:;
                }
            }
            break;

            case SDL_QUIT:
                m_bIsRunning = false;
            break;

            default:;
        }
    }
}



void ScatteringDemo::update()
{
    Application::update();
    m_oSky.setTranslate( m_opActiveCamera->getPosition().x,
                         m_opActiveCamera->getPosition().y - (m_opActiveCamera->getPosition().y /2000.0f ),
                         m_opActiveCamera->getPosition().z );
}



void ScatteringDemo::draw()
{
    m_opScreen->beginRender();

    Application::draw();

    drawInfoText();
    drawHelpText();

    m_opScreen->endRender();
}



void ScatteringDemo::drawInfoText()
{
    char buff[256];
    sprintf(buff, "Posicao: (%.2f , %.2f , %.2f)   -   Velocidade: (%.2f , %.2f , %.2f)",
            m_oFlyingCamera.getTranslate().x,
            m_oFlyingCamera.getTranslate().y,
            m_oFlyingCamera.getTranslate().z,
            m_oFlyingCamera.getVelocity().x ,
            m_oFlyingCamera.getVelocity().y,
            m_oFlyingCamera.getVelocity().z);
    m_opInfoText->DrawStr(10, 10, buff);

    sprintf(buff, "FPS = %.2f", m_oClock.GetFrameRate());
    m_opInfoText->DrawStr(SCREEN_WIDTH - 8*strlen(buff)-10, 10, buff);
}



void ScatteringDemo::drawHelpText()
{
    m_opHelpText->DrawStr(10, 30, " Setas: Controla a direcao da Camera");
    m_opHelpText->DrawStr(10, 40, "   [a]: Move para frente");
    m_opHelpText->DrawStr(10, 70, " [ESC]: Sair do demo");
}
