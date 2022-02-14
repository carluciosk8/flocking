/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Texture.h"

#include <string>
#include <stdexcept>

using std::runtime_error;
using std::string;

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


TextureState::TextureState()
: m_iWidth(0),
  m_iHeight(0),
  m_uiTexHandle(0)
{
    printf("Creating Texture\n");
}



TextureState::TextureState(const char* cpFile)
{
    printf("Creating Texture\n");
    load(cpFile);
}



TextureState::~TextureState()
{
    printf("Deleting Texture\n");
    glDeleteTextures(1, &m_uiTexHandle);
}



void TextureState::enable()
{
    glEnable(GL_TEXTURE_2D);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, m_uiTexHandle);
}



void TextureState::disable()
{
    glDisable(GL_TEXTURE_2D);
}



void TextureState::load(const char* cpFile)
{
    SDL_Surface *surface;
    int mode;

    surface = IMG_Load(cpFile);

    if (!surface)
        throw runtime_error( string("Couldn't load image: ") + string(cpFile) );

    if (surface->format->BytesPerPixel == 3)
        mode = GL_RGB;
    else if (surface->format->BytesPerPixel == 4)
        mode = GL_RGBA;
    else
    {
        SDL_FreeSurface(surface);
        throw runtime_error( string("Invalid BPP format for image: ") + string(cpFile) );
    }

    m_iWidth = surface->w;
    m_iHeight = surface->h;

    glGenTextures(1, &m_uiTexHandle);
    glBindTexture(GL_TEXTURE_2D, m_uiTexHandle);
    glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
    //glTexImage2D(GL_TEXTURE_2D, 0, mode, m_iWidth, m_iHeight, 0, mode, GL_UNSIGNED_BYTE, surface->pixels);

    if (surface->format->BytesPerPixel == 3)
        gluBuild2DMipmaps( GL_TEXTURE_2D, 3, m_iWidth, m_iHeight, GL_RGB, GL_UNSIGNED_BYTE, surface->pixels );
    else if (surface->format->BytesPerPixel == 4)
        gluBuild2DMipmaps( GL_TEXTURE_2D, 3, m_iWidth, m_iHeight, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels );

    SDL_FreeSurface(surface);
}
