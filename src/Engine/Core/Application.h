/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <vector>

using std::vector;

#include "Clock.h"
#include "Timer.h"


class Screen;
class Camera;
class Scene;

class EventHandler
{
    public:
        EventHandler(int type, void* pApp, void (*handler)(void*)) : m_iType(type), app(pApp), callback(handler){}

        void doIt() { (*callback)(app); }
        int getType() { return m_iType; }

    private:
        int  m_iType;
        void* app;
        void (*callback)(void*);
};


#define  DECLARE_CALLBACK(func)             \
    void func();                            \
    static void func ## Wrapper(void* ptr)


#define  IMPLEMENT_CALLBACK(class,func)     \
    void class::func##Wrapper(void* ptr)    \
    {                                       \
        class* mySelf = (class*) ptr;       \
        mySelf->func();                     \
    }                                       \
                                            \
    void class::func()



class Application
{
    public:
        Application();
        virtual ~Application();


        void run();

        virtual void init()=0;
        virtual void shutdown()=0;

        void registerKeyDownEvent(EventHandler*);
        void registerKeyUpEvent(EventHandler*);


    protected:
        virtual void handleEvents();
        virtual void update();
        virtual void draw();

        void setActiveScene(Scene* opScene);
        void setActiveCamera(Camera* opCamera);


    protected:
        bool  m_bIsRunning;

        Screen*  m_opScreen;
        Camera*  m_opActiveCamera;
        Scene*  m_opActiveScene;

        Clock  m_oClock;
        Timer  m_oTimer;

        vector<EventHandler*>  m_oEventKeyDownHandlerList;
        vector<EventHandler*>  m_oEventKeyUpHandlerList;
};



#define  REGISTER_KEYDOWN_CALLBACK(type,func)  \
    registerKeyDownEvent(new EventHandler(type, this, func##Wrapper) )

#define  REGISTER_KEYUP_CALLBACK(type,func)  \
    registerKeyUpEvent(new EventHandler(type, this, func##Wrapper) )



#endif
