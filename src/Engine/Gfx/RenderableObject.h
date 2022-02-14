/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __RENDERABLEOBJECT_H__
#define __RENDERABLEOBJECT_H__


class RenderableObject
{
    public:
        RenderableObject();
        virtual ~RenderableObject();

        virtual void render()=0;


    protected:
};


#endif
