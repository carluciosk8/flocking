/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Screen.h"

#include <SDL/SDL.h>

#include <GL/glew.h>

#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;



Screen::Screen(const char* cpName, int iWidth, int iHeight, bool bFullScreen)
: m_iWidth(iWidth),
  m_iHeight(iHeight),
  m_bFullScreen(bFullScreen)
{
    printf("Initializing SDL\n");
    int  iFlags = SDL_OPENGL;


    if ( bFullScreen )
        iFlags |= SDL_FULLSCREEN;

    if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 )
        throw runtime_error( string("Couldn't initialize SDL: ") + string(SDL_GetError()) );

    SDL_WM_SetCaption(cpName,0);

    SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
    SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 16 );
    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    const SDL_VideoInfo* video = SDL_GetVideoInfo();

    if( !video )
        throw runtime_error( string("Couldn't get video information: ") + string(SDL_GetError()) );

    if( SDL_SetVideoMode( iWidth, iHeight, video->vfmt->BitsPerPixel, iFlags ) == 0 )
        throw runtime_error( string("Couldn't set video mode: ") + string(SDL_GetError()) );

    glewInit();

    glShadeModel(GL_SMOOTH);
    glClearColor(0.3f, 0.3f ,0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);
}



Screen::~Screen()
{
    printf("Quitting SDL\n");
    SDL_Quit();
}



void Screen::beginRender()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}



void Screen::endRender()
{
    SDL_GL_SwapBuffers();
}
