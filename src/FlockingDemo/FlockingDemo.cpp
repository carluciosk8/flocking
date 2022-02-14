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
#include "../Engine/Gfx/FogState.h"
#include "../Engine/Gfx/LightState.h"
#include "../Engine/Gfx/Texture.h"
#include "../Engine/Gfx/Terrain.h"

#include "FlockingDemo.h"
#include "Boid.h"


#define STEP             0.05f
#define INITIAL_BOIDS    50


FlockingDemo::FlockingDemo(int iWidth, int iHeight)
:
    Application(),
    m_oTerrain("Terreno"),
    m_oSky("Ceu"),
    m_oLeaderBoid("Controlable Boid"),
    m_oTerrainModel(),
    m_bShowHelpText(false)
{
    m_opScreen = new Screen("Flocking Demo", iWidth, iHeight, false);
    m_opViewport = new Viewport(0, 0, iWidth, iHeight);
    m_opInfoText = new TextBox(10, iWidth - 10, 10, 20);
    m_opHelpText = new TextBox(10, iWidth - 10, 20, iHeight - 400);
    m_opLeaderBoidModel = new CMd2("resources/leader2.md2");
    m_opTowerCamera = new Camera(60.0f, float(iWidth)/iHeight, 0.5f, 350000.0f);
    m_opFlockBehindCamera = new Camera(60.0f, float(iWidth)/iHeight, 0.5f, 350000.0f);
    m_opFlockSideCamera = new Camera(60.0f, float(iWidth)/iHeight, 0.5f, 350000.0f);


    m_opInfoText->SetColor(TextBox::YELLOW);
    m_opHelpText->SetColor(TextBox::WHITE);
}



FlockingDemo::~FlockingDemo()
{
    delete m_opFlockSideCamera;
    delete m_opFlockBehindCamera;
    delete m_opTowerCamera;
    delete m_opLeaderBoidModel;
    delete m_opHelpText;
    //delete m_opDebugText;
    delete m_opInfoText;
    delete m_opViewport;
    delete m_opScreen;
}



void FlockingDemo::init()
{
    m_opViewport->setViewport();

//     std::cout << "BetaRayleigh: " << m_oAtm.GetBetaRayleigh() << std::endl;
//     std::cout << "BetaDashRayleigh: " << m_oAtm.GetBetaDashRayleigh() << std::endl;
//     std::cout << "BetaMie: " << m_oAtm.GetBetaMie() << std::endl;
//     std::cout << "BetaDashMie: " << m_oAtm.GetBetaDashMie() << std::endl;

    // Create Terrain
    m_oTerrainModel.generate(300, 60.0f);
    m_oTerrain.addObject(&m_oTerrainModel);
    m_oTerrain.addRenderState(new TextureState("resources/terrain.jpg"));
    m_oScene.addObject(&m_oTerrain);

    // Create Skydome
    m_oSkyModel.generate(8, 30000.0f);
    m_oSky.addObject(&m_oSkyModel);
    m_oSky.addRenderState(new TextureState("resources/skydome1.jpg"));
    m_oScene.addObject(&m_oSky);

//    m_oSun.SetSunThetaPhi(M_PI/4.0, M_PI/2.0);

    // Create Leader Boid
    m_oLeaderBoid.addObject(m_opLeaderBoidModel);
    m_oLeaderBoid.addRenderState(new TextureState("resources/leader.png"));
    m_oLeaderBoid.setTranslate(-10.0f, m_oTerrainModel.getHeight(0.0f, 0.0f) + 50.0f, 0.0f);
    m_oLeaderBoid.setScale(0.01f);
    m_oScene.addObject(&m_oLeaderBoid);
    m_opLeaderBoidModel->setAnimateOn(true, 0, 29);

    // Create 30 Autonomous Boids
    Boid::setLeader(&m_oLeaderBoid);
    Boid::setTerrain(&m_oTerrainModel);
    for (int i=0 ; i<INITIAL_BOIDS ; ++i)
        addBoid();

    // Add directional light to scene
    float4 vSpecular(0.0f, 0.0f, 0.0f, 1.0f);
    float4 vAmbient(0.8f, 0.8f, 0.8f, 1.0f);
    float4 vDiffuse(0.8f, 0.8f, 0.8f, 1.0f);
    float3 vDirection(-0.16001f, -0.86803f, 0.47002f);
    m_oScene.addRenderState(new LightState(vSpecular, vAmbient, vDiffuse, vDirection));

    // Set active camera
    m_opActiveCamera = m_opFlockSideCamera;

    // Set active scene
    setActiveScene(&m_oScene);


    // Register callback to events handled by application
    REGISTER_KEYDOWN_CALLBACK(SDLK_UP, FlockingDemo::onPressUp);
    REGISTER_KEYDOWN_CALLBACK(SDLK_DOWN, FlockingDemo::onPressDown);
    REGISTER_KEYDOWN_CALLBACK(SDLK_LEFT, FlockingDemo::onPressLeft);
    REGISTER_KEYDOWN_CALLBACK(SDLK_RIGHT, FlockingDemo::onPressRight);
    REGISTER_KEYDOWN_CALLBACK(SDLK_a, FlockingDemo::onPressAccel);
    REGISTER_KEYDOWN_CALLBACK(SDLK_z, FlockingDemo::onPressDecel);
    REGISTER_KEYDOWN_CALLBACK(SDLK_j, FlockingDemo::onPressAccel2);
    REGISTER_KEYDOWN_CALLBACK(SDLK_m, FlockingDemo::onPressDecel2);
    REGISTER_KEYDOWN_CALLBACK(SDLK_w, FlockingDemo::onPressIncDKs);
    REGISTER_KEYDOWN_CALLBACK(SDLK_s, FlockingDemo::onPressDecDKs);
    REGISTER_KEYDOWN_CALLBACK(SDLK_e, FlockingDemo::onPressIncDKa);
    REGISTER_KEYDOWN_CALLBACK(SDLK_d, FlockingDemo::onPressDecDKa);
    REGISTER_KEYDOWN_CALLBACK(SDLK_r, FlockingDemo::onPressIncDKc);
    REGISTER_KEYDOWN_CALLBACK(SDLK_f, FlockingDemo::onPressDecDKc);
    REGISTER_KEYDOWN_CALLBACK(SDLK_t, FlockingDemo::onPressIncDKg);
    REGISTER_KEYDOWN_CALLBACK(SDLK_g, FlockingDemo::onPressDecDKg);

    REGISTER_KEYUP_CALLBACK(SDLK_UP, FlockingDemo::onReleaseUp);
    REGISTER_KEYUP_CALLBACK(SDLK_DOWN, FlockingDemo::onReleaseDown);
    REGISTER_KEYUP_CALLBACK(SDLK_LEFT, FlockingDemo::onReleaseLeft);
    REGISTER_KEYUP_CALLBACK(SDLK_RIGHT, FlockingDemo::onReleaseRight);
    REGISTER_KEYUP_CALLBACK(SDLK_a, FlockingDemo::onReleaseAccel);
    REGISTER_KEYUP_CALLBACK(SDLK_z, FlockingDemo::onReleaseDecel);
    REGISTER_KEYUP_CALLBACK(SDLK_j, FlockingDemo::onReleaseAccel2);
    REGISTER_KEYUP_CALLBACK(SDLK_m, FlockingDemo::onReleaseDecel2);
    REGISTER_KEYUP_CALLBACK(SDLK_w, FlockingDemo::onReleaseIncDKs);
    REGISTER_KEYUP_CALLBACK(SDLK_s, FlockingDemo::onReleaseDecDKs);
    REGISTER_KEYUP_CALLBACK(SDLK_e, FlockingDemo::onReleaseIncDKa);
    REGISTER_KEYUP_CALLBACK(SDLK_d, FlockingDemo::onReleaseDecDKa);
    REGISTER_KEYUP_CALLBACK(SDLK_r, FlockingDemo::onReleaseIncDKc);
    REGISTER_KEYUP_CALLBACK(SDLK_f, FlockingDemo::onReleaseDecDKc);
    REGISTER_KEYUP_CALLBACK(SDLK_t, FlockingDemo::onReleaseIncDKg);
    REGISTER_KEYUP_CALLBACK(SDLK_g, FlockingDemo::onReleaseDecDKg);

    REGISTER_KEYDOWN_CALLBACK(SDLK_h, FlockingDemo::onPressHelp);
    REGISTER_KEYDOWN_CALLBACK(SDLK_KP_PLUS, FlockingDemo::onPressIncBoid);
    REGISTER_KEYDOWN_CALLBACK(SDLK_KP_MINUS, FlockingDemo::onPressDecBoid);
    REGISTER_KEYDOWN_CALLBACK(SDLK_1, FlockingDemo::onPressChangeCameraLeader);
    REGISTER_KEYDOWN_CALLBACK(SDLK_2, FlockingDemo::onPressChangeCameraTower);
    REGISTER_KEYDOWN_CALLBACK(SDLK_3, FlockingDemo::onPressChangeCameraBehind);
    REGISTER_KEYDOWN_CALLBACK(SDLK_4, FlockingDemo::onPressChangeCameraSide);
    REGISTER_KEYDOWN_CALLBACK(SDLK_p, FlockingDemo::onPressPause);
    REGISTER_KEYDOWN_CALLBACK(SDLK_ESCAPE, FlockingDemo::onPressQuit);

    //REGISTER_KEYDOWN_CALLBACK(SDL onMouseWheelUp);
    //REGISTER_KEYDOWN_CALLBACK( onMouseWheelDown);
}



void FlockingDemo::shutdown()
{
    while (Boid::getBoidsList().size() > 0)
        remBoid();
}



void FlockingDemo::update()
{
    Application::update();

    //
    // Update Tower Camera
    m_opTowerCamera->setPosition(float3(0.0f, m_oTerrainModel.getHeight(0.0f, 0.0f) + 50.0f, 0.0f));
    m_opTowerCamera->lookAt(Boid::getFlockCenter());

    //
    // Update Behind Flocking Camera
    float3  pos = Boid::getFlockCenter() - Boid::getFlockVelocity() * 30.0f;
    if (pos.y < m_oTerrainModel.getHeight(pos.x, pos.z) + 10.0f )
        pos.y = m_oTerrainModel.getHeight(pos.x, pos.z) + 10.0f;
    m_opFlockBehindCamera->setPosition(pos);
    m_opFlockBehindCamera->lookAt(Boid::getFlockCenter());

    //
    // Update Side Flocking Camera
    float3  side;
    side.cross(Boid::getFlockVelocity(), float3::UNIT_Y);
    side.normalize();
    pos = Boid::getFlockCenter() - side*30.0f;
    if (pos.y < m_oTerrainModel.getHeight(pos.x, pos.z) + 10.0f )
        pos.y = m_oTerrainModel.getHeight(pos.x, pos.z) + 10.0f;
    m_opFlockSideCamera->setPosition(pos);
    m_opFlockSideCamera->lookAt(Boid::getFlockCenter());


    //
    // Update Boid State
    Boid::calcFlockCenter();
    Boid::s_Ks += Boid::s_DKs;
    Boid::s_Ka += Boid::s_DKa;
    Boid::s_Kc += Boid::s_DKc;
    Boid::s_Kg += Boid::s_DKg;
}



void FlockingDemo::draw()
{
    m_opScreen->beginRender();

    Application::draw();

    glDisable(GL_LIGHTING);
    drawInfoText();
    if (m_bShowHelpText) drawHelpText();
    glEnable(GL_LIGHTING);

    m_opScreen->endRender();
}



void FlockingDemo::drawInfoText()
{
    char buff[256];
    sprintf(buff, "Posicao: (%.2f , %.2f , %.2f)   -   Velocidade: (%.2f , %.2f , %.2f)", m_oLeaderBoid.getTranslate().x,
                                                                                          m_oLeaderBoid.getTranslate().y,
                                                                                          m_oLeaderBoid.getTranslate().z,
                                                                                          m_oLeaderBoid.getVelocity().x ,
                                                                                          m_oLeaderBoid.getVelocity().y,
                                                                                          m_oLeaderBoid.getVelocity().z);
    m_opInfoText->DrawStr(10, 0, buff);

    sprintf(buff, "# of Boids: %d  -  Ks: %.4f  -  Ka: %.4f  -  Kc: %.4f  -  Kg: %.4f", Boid::getBoidsList().size() , Boid::s_Ks, Boid::s_Ka, Boid::s_Kc, Boid::s_Kg);
    m_opInfoText->DrawStr(10, SCREEN_HEIGHT - 10, buff);

    sprintf(buff, "FPS = %.2f", m_oClock.GetFrameRate());
    m_opInfoText->DrawStr(SCREEN_WIDTH - 100, 0, buff);
}



void FlockingDemo::drawHelpText()
{
    m_opHelpText->DrawStr(10, 30,  " Setas: Controla a direcao do Boid lider                                                         ");
    m_opHelpText->DrawStr(10, 40,  " [a]: Aumenta a vel. do Boid lider                                                               ");
    m_opHelpText->DrawStr(10, 50,  " [z]: Diminui a vel. do Boid lider                                                               ");
    m_opHelpText->DrawStr(10, 60,  " [+]: Aumenta o numero de Boids                                                                  ");
    m_opHelpText->DrawStr(10, 70,  " [-]: Diminui o numero de Boids                                                                  ");
    m_opHelpText->DrawStr(10, 80,  " [1]: Camera no Boid lider                                                                       ");
    m_opHelpText->DrawStr(10, 90,  " [2]: Camera na Torre de Observacao                                                              ");
    m_opHelpText->DrawStr(10, 100, " [3]: Camera atras do bando                                                                      ");
    m_opHelpText->DrawStr(10, 110, " [4]: Camera ao lado do bando                                                                    ");
    m_opHelpText->DrawStr(10, 120, " [w]: Aumenta Ks (Constante de separacao)                                                        ");
    m_opHelpText->DrawStr(10, 130, " [s]: Diminui Ks                                                                                 ");
    m_opHelpText->DrawStr(10, 140, " [e]: Aumenta Ka (Constante de alinhamento)                                                      ");
    m_opHelpText->DrawStr(10, 150, " [d]: Diminui Ka                                                                                 ");
    m_opHelpText->DrawStr(10, 160, " [r]: Aumenta Kc (Constante de coesao)                                                           ");
    m_opHelpText->DrawStr(10, 170, " [f]: Diminui Kc                                                                                 ");
    m_opHelpText->DrawStr(10, 180, " [t]: Aumenta Kg (Constante de objetivo)                                                         ");
    m_opHelpText->DrawStr(10, 190, " [g]: Diminui Kg                                                                                 ");
    m_opHelpText->DrawStr(10, 200, " [p]: Liga/desliga pausa                                                                         ");
    m_opHelpText->DrawStr(10, 210, "                                                                                                 ");
    m_opHelpText->DrawStr(10, 220, "                                                                                                 ");
    m_opHelpText->DrawStr(10, 230, " [ESC]: Sair do demo                                                                             ");
}



void FlockingDemo::addBoid()
{
    Boid* opBoid = new Boid("Boid");

    float x = newRand(m_oLeaderBoid.getTranslate().x - 50.0f , m_oLeaderBoid.getTranslate().x + 50.0f);
    float y = newRand(m_oLeaderBoid.getTranslate().y - 50.0f , m_oLeaderBoid.getTranslate().y + 50.0f);
    float z = newRand(m_oLeaderBoid.getTranslate().z - 50.0f , m_oLeaderBoid.getTranslate().z + 50.0f);

    CMd2*  opBoidModel = new CMd2("resources/corvo.md2");

    opBoidModel->setAnimateOn(true, 0, 29);
    opBoid->addObject(opBoidModel);
    opBoid->setTranslate(x, y, z);
    opBoid->setScale(0.01f);
    opBoid->addRenderState(new TextureState("resources/corvo.png"));

    m_oScene.addObject(opBoid);
}



void FlockingDemo::remBoid()
{
    Boid* opBoid = Boid::getBoidsList().front();
    Boid::getBoidsList().pop_front();
    delete opBoid->getObject();
    m_oScene.remObject(opBoid);
    delete opBoid;
}



IMPLEMENT_CALLBACK(FlockingDemo, onPressUp)       { m_oLeaderBoid.setVelPitch(-0.5f); }
IMPLEMENT_CALLBACK(FlockingDemo, onPressDown)     { m_oLeaderBoid.setVelPitch(0.5f); }
IMPLEMENT_CALLBACK(FlockingDemo, onPressLeft)     { m_oLeaderBoid.setVelYaw(0.5f); }
IMPLEMENT_CALLBACK(FlockingDemo, onPressRight)    { m_oLeaderBoid.setVelYaw(-0.5f); }
IMPLEMENT_CALLBACK(FlockingDemo, onPressAccel)    { m_oLeaderBoid.setAcc(3.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onPressDecel)    { m_oLeaderBoid.setAcc(-3.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onPressAccel2)   { m_oLeaderBoid.setAcc(3.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onPressDecel2)   { m_oLeaderBoid.setAcc(-3.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onPressIncDKs)   { Boid::s_DKs = +STEP; }
IMPLEMENT_CALLBACK(FlockingDemo, onPressDecDKs)   { Boid::s_DKs = -STEP; }
IMPLEMENT_CALLBACK(FlockingDemo, onPressIncDKa)   { Boid::s_DKa = +STEP; }
IMPLEMENT_CALLBACK(FlockingDemo, onPressDecDKa)   { Boid::s_DKa = -STEP; }
IMPLEMENT_CALLBACK(FlockingDemo, onPressIncDKc)   { Boid::s_DKc = +STEP; }
IMPLEMENT_CALLBACK(FlockingDemo, onPressDecDKc)   { Boid::s_DKc = -STEP; }
IMPLEMENT_CALLBACK(FlockingDemo, onPressIncDKg)   { Boid::s_DKg = +STEP; }
IMPLEMENT_CALLBACK(FlockingDemo, onPressDecDKg)   { Boid::s_DKg = -STEP; }

IMPLEMENT_CALLBACK(FlockingDemo, onReleaseUp)     { m_oLeaderBoid.setVelPitch(0.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseDown)   { m_oLeaderBoid.setVelPitch(0.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseLeft)   { m_oLeaderBoid.setVelYaw(0.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseRight)  { m_oLeaderBoid.setVelYaw(0.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseAccel)  { m_oLeaderBoid.setAcc(0.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseDecel)  { m_oLeaderBoid.setAcc(0.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseAccel2) { m_oLeaderBoid.setAcc(0.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseDecel2) { m_oLeaderBoid.setAcc(0.0f); }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseIncDKs) { Boid::s_DKs = 0; }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseDecDKs) { Boid::s_DKs = 0; }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseIncDKa) { Boid::s_DKa = 0; }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseDecDKa) { Boid::s_DKa = 0; }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseIncDKc) { Boid::s_DKc = 0; }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseDecDKc) { Boid::s_DKc = 0; }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseIncDKg) { Boid::s_DKg = 0; }
IMPLEMENT_CALLBACK(FlockingDemo, onReleaseDecDKg) { Boid::s_DKg = 0; }


IMPLEMENT_CALLBACK(FlockingDemo, onPressIncBoid)
{
    if (Boid::getBoidsList().size() < 100)
        addBoid();
}

IMPLEMENT_CALLBACK(FlockingDemo, onPressDecBoid)
{
    if (Boid::getBoidsList().size() > 0)
        remBoid();
}

IMPLEMENT_CALLBACK(FlockingDemo, onPressChangeCameraLeader) { m_opActiveCamera = &m_oLeaderBoid.getCamera(); }
IMPLEMENT_CALLBACK(FlockingDemo, onPressChangeCameraTower)  { m_opActiveCamera = m_opTowerCamera; }
IMPLEMENT_CALLBACK(FlockingDemo, onPressChangeCameraBehind) { m_opActiveCamera = m_opFlockBehindCamera; }
IMPLEMENT_CALLBACK(FlockingDemo, onPressChangeCameraSide)   { m_opActiveCamera = m_opFlockSideCamera; }

IMPLEMENT_CALLBACK(FlockingDemo, onPressHelp)
{
    m_bShowHelpText = m_bShowHelpText ? false : true;

//    if (m_bShowHelpText)
//        m_bShowHelpText = false;
//    else
//        m_bShowHelpText = true;
}

IMPLEMENT_CALLBACK(FlockingDemo, onPressPause)
{
    m_oTimer.pause( m_oTimer.isPaused() ? false : true );
//    if (m_oTimer.isPaused())
//        m_oTimer.pause(false);
//    else
//        m_oTimer.pause(true);
}

IMPLEMENT_CALLBACK(FlockingDemo, onPressQuit)
{
    m_bIsRunning = false;
}
