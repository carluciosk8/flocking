/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __RENDERSTATE_H__
#define __RENDERSTATE_H__


class RenderState
{
    public:
		virtual ~RenderState() {}

		virtual void enable()=0;
        virtual void disable()=0;
};


#endif
