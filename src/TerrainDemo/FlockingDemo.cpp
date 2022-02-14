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
#include "../Engine/Gfx/ShaderState.h"
#include "../Engine/Gfx/FogState.h"
#include "../Engine/Gfx/LightState.h"
#include "../Engine/Gfx/Texture.h"
#include "../Engine/Gfx/Terrain.h"

#include "FlockingDemo.h"
#include "Boid.h"


#define STEP  0.05f


FlockingDemo::FlockingDemo()
:
    Application(),
    m_oTerrain("Terreno"),
    m_oLeaderBoid("Controlable Boid")
{
    m_opScreen = new Screen("Flocking Demo", SCREEN_WIDTH, SCREEN_HEIGHT, false);
	m_opViewport = new Viewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    m_opInfoText = new TextBox(10, SCREEN_WIDTH - 10, 10, 20);
	m_opDebugText = new TextBox(10, SCREEN_WIDTH - 10, 10, SCREEN_HEIGHT - 10);
    m_opHelpText = new TextBox(10, SCREEN_WIDTH - 10, 20, SCREEN_HEIGHT - 400);
    m_opLeaderBoidModel = new CMd2("resources/leader.md2");
    m_opTowerCamera = new Camera(60.0f, float(SCREEN_WIDTH)/SCREEN_HEIGHT, 0.5f, 10000.0f);
	m_opFlockBehindCamera = new Camera(60.0f, float(SCREEN_WIDTH)/SCREEN_HEIGHT, 0.5f, 10000.0f);
	m_opFlockSideCamera = new Camera(60.0f, float(SCREEN_WIDTH)/SCREEN_HEIGHT, 0.5f, 10000.0f);


	m_opInfoText->SetColor(TextBox::YELLOW);
    m_opHelpText->SetColor(TextBox::WHITE);
	m_opDebugText->SetColor(TextBox::GREY);
}



FlockingDemo::~FlockingDemo()
{
	delete m_opFlockSideCamera;
	delete m_opFlockBehindCamera;
	delete m_opTowerCamera;
	delete m_opLeaderBoidModel;
	delete m_opHelpText;
	delete m_opDebugText;
	delete m_opInfoText;
	delete m_opViewport;
	delete m_opScreen;
}



void FlockingDemo::init()
{
    m_opViewport->setViewport();

    // Create Terrain
    m_oTerrainModel.generate();
    m_oTerrain.addObject(&m_oTerrainModel);
    m_oTerrain.addRenderState(new TextureState("resources/terrain.jpg"));
    m_oScene.addObject(&m_oTerrain);

    // Create Leader Boid
    m_oLeaderBoid.addObject(m_opLeaderBoidModel);
    m_oLeaderBoid.addRenderState(new TextureState("resources/leader.png"));
    m_oLeaderBoid.setTranslate( -10.0f , m_oTerrainModel.getHeight(0.0f, 0.0f) + 50.0f , 0.0f );
    m_oLeaderBoid.setScale(0.012f);
    m_oScene.addObject(&m_oLeaderBoid);
	m_opLeaderBoidModel->setAnimateOn(true, 0, 29);

    // Create 30 Autonomous Boids
    Boid::setLeader(&m_oLeaderBoid);
    for (int i=0 ; i<30 ; ++i)
        addBoid();

	// Add directional light to scene
	float4 vSpecular(0.0f, 0.0f, 0.0f, 1.0f);
	float4 vAmbient(0.5f, 0.5f, 0.5f, 1.0f);
	float4 vDiffuse(0.5f, 0.5f, 0.5f, 1.0f);
	float3 vDirection(1.0f, 1.0f, 1.0f);
	m_oScene.addRenderState(new LightState(vSpecular, vAmbient, vDiffuse, vDirection));

    // Set active camera
    m_opActiveCamera = &m_oLeaderBoid.getCamera();


	// Set active scene
    //m_oScene.addRenderState(new ShaderState("shaders/toon_vs.glsl", "shaders/toon_fs.glsl"));
    m_oScene.addRenderState(new ShaderState("shaders/phong_vs.glsl", "shaders/phong_fs.glsl"));
	//m_oScene.addRenderState(new FogState(10.0f, 500.0f, 0.001f, float4(0.3f, 0.3f, 0.3f, 1.0f) ));
	setActiveScene(&m_oScene);

    Boid::setTerrain(&m_oTerrainModel);
}



void FlockingDemo::shutdown()
{
    while (Boid::getBoidsList().size() > 0)
        remBoid();
}



void FlockingDemo::handleEvents()
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
                        m_oLeaderBoid.setVelPitch(-0.5f);
                    }
                    break;

                    case SDLK_DOWN:
                    {
                        m_oLeaderBoid.setVelPitch(0.5f);
                    }
                    break;

                    case SDLK_LEFT:
                    {
                        m_oLeaderBoid.setVelYaw(0.5f);
                    }
                    break;

                    case SDLK_RIGHT:
                    {
                        m_oLeaderBoid.setVelYaw(-0.5f);
                    }
                    break;

                    case SDLK_a:
                    {
                        m_oLeaderBoid.setAcc(3.0f);
                    }
                    break;

                    case SDLK_z:
                    {
                        m_oLeaderBoid.setAcc(-3.0f);
                    }
                    break;

                    case SDLK_KP_PLUS:
                    {
						if (Boid::getBoidsList().size() < 100)
							addBoid();
                    }
                    break;

                    case SDLK_KP_MINUS:
                    {
						if (Boid::getBoidsList().size() > 0)
	                        remBoid();
                    }
                    break;

                    case SDLK_1:
                    {
                        m_opActiveCamera = &m_oLeaderBoid.getCamera();
                    }
                    break;

                    case SDLK_2:
                    {
                        m_opActiveCamera = m_opTowerCamera;
                    }
                    break;

                    case SDLK_3:
                    {
                        m_opActiveCamera = m_opFlockBehindCamera;
                    }
                    break;

                    case SDLK_4:
                    {
                        m_opActiveCamera = m_opFlockSideCamera;
                    }
                    break;

                    case SDLK_w:
                    {
						Boid::s_DKs = +STEP;
                    }
                    break;

                    case SDLK_s:
                    {
						Boid::s_DKs = -STEP;
                    }
                    break;

                    case SDLK_e:
                    {
						Boid::s_DKa = +STEP;
                    }
                    break;

                    case SDLK_d:
                    {
						Boid::s_DKa = -STEP;
                    }
                    break;

                    case SDLK_r:
                    {
						Boid::s_DKc = +STEP;
                    }
                    break;

                    case SDLK_f:
                    {
						Boid::s_DKc = -STEP;
                    }
                    break;

                    case SDLK_t:
                    {
						Boid::s_DKg = +STEP;
                    }
                    break;

                    case SDLK_g:
                    {
						Boid::s_DKg = -STEP;
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
                        m_oLeaderBoid.setVelPitch(0.0f);
                    }
                    break;

                    case SDLK_DOWN:
                    {
                        m_oLeaderBoid.setVelPitch(0.0f);
                    }
                    break;

                    case SDLK_LEFT:
                    {
                        m_oLeaderBoid.setVelYaw(0.0f);
                    }
                    break;

                    case SDLK_RIGHT:
                    {
                        m_oLeaderBoid.setVelYaw(0.0f);
                    }
                    break;

                    case SDLK_a:
                    {
                        m_oLeaderBoid.setAcc(0.0f);
                    }
                    break;

                    case SDLK_z:
                    {
                        m_oLeaderBoid.setAcc(0.0f);
                    }
                    break;

					case SDLK_w:
                    {
						Boid::s_DKs = 0.0;
                    }
                    break;

                    case SDLK_s:
                    {
						Boid::s_DKs = 0.0;
                    }
                    break;

					case SDLK_e:
                    {
						Boid::s_DKa = 0.0;
                    }
                    break;

                    case SDLK_d:
                    {
						Boid::s_DKa = 0.0;
                    }
                    break;

					case SDLK_r:
                    {
						Boid::s_DKc = 0.0;
                    }
                    break;

                    case SDLK_f:
                    {
						Boid::s_DKc = 0.0;
                    }
                    break;

					case SDLK_t:
                    {
						Boid::s_DKg = 0.0;
                    }
                    break;

                    case SDLK_g:
                    {
						Boid::s_DKg = 0.0;
                    }
                    break;

                    case SDLK_p:
                    {
						if (m_oTimer.isPaused())
							m_oTimer.pause(false);
						else
							m_oTimer.pause(true);
                    }
                    break;
                    default:;
                }
            }
            break;

			case SDL_QUIT:
                m_bIsRunning = false;
            break;

                    //default:;
        }
    }
}



void FlockingDemo::update()
{
	Application::update();
	Boid::calcFlockCenter();

	//
	// Update Cameras
    m_opTowerCamera->setPosition(float3(0.0f, m_oTerrainModel.getHeight(0.0f, 0.0f) + 50.0f, 0.0f));
    m_opTowerCamera->setForward(Boid::getFlockCenter() - m_opTowerCamera->getPosition());

    float3  pos = Boid::getFlockCenter() - Boid::getFlockVelocity() * 30.0f;
	float3  forward;
	if (pos.y < m_oTerrainModel.getHeight(pos.x, pos.z) + 10.0f )
		pos.y = m_oTerrainModel.getHeight(pos.x, pos.z) + 10.0f;
	forward = Boid::getFlockCenter() - pos;
	m_opFlockBehindCamera->setPosition(pos);
	m_opFlockBehindCamera->setForward(forward);

	float3  side;
	side.cross(Boid::getFlockVelocity(), float3::UNIT_Y);
	side.normalize();
	pos = Boid::getFlockCenter() - side*30.0f;
	if (pos.y < m_oTerrainModel.getHeight(pos.x, pos.z) + 10.0f )
		pos.y = m_oTerrainModel.getHeight(pos.x, pos.z) + 10.0f;
	forward = Boid::getFlockCenter() - pos;
	m_opFlockSideCamera->setPosition(pos);
	m_opFlockSideCamera->setForward(forward);


	//
	// Update Constants
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
    drawHelpText();
	m_opDebugText->Draw();
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
    m_opInfoText->DrawStr(10, 10, buff);

    sprintf(buff, "FPS = %.2f", m_oClock.GetFrameRate());
    m_opInfoText->DrawStr(10, 590, buff);
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
// 	Asteroid*  opAsteroidModel = new Asteroid;
// 	opAsteroidModel->generate(rand(),
// 		                      newRand(25.0, 100.0),
// 							  newRand(1.0, 2.0),
// 							  newRand(0.25, 0.75),
// 							  4);

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
