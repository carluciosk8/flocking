/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __TEXTURE_H__
#define __TEXTURE_H__


#include "RenderState.h"

#include <GL/glew.h>


class TextureState : public RenderState
{
    public:
        TextureState();
        TextureState(const char* cpFile);
        virtual ~TextureState();

        virtual void enable();
        virtual void disable();

        void load(const char* cpFile);


    protected:
        int  m_iWidth;
        int  m_iHeight;
        GLuint m_uiTexHandle;
};


#endif
