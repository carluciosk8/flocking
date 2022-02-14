/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "WireframeState.h"

#include <GL/glew.h>


WireframeState::WireframeState()
{}



WireframeState::~WireframeState()
{}



void WireframeState::enable()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}



void WireframeState::disable()
{
    glPolygonMode(GL_FRONT, GL_FILL);
}
