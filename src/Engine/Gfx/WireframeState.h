/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __WIREFRAMESTATE_H__
#define __WIREFRAMESTATE_H__


#include "RenderState.h"


class WireframeState : public RenderState
{
    public:
        WireframeState();
        virtual ~WireframeState();

        virtual void enable();
        virtual void disable();
};


#endif
