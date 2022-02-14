/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "TimeSourceSDL.h"
#include <SDL/SDL.h>

TimeSourceSDL::TimeSourceSDL()
{
}



TimeSourceSDL::~TimeSourceSDL()
{
}



double TimeSourceSDL::getTime() const
{
    return (double)SDL_GetTicks()/1000.0;
}
