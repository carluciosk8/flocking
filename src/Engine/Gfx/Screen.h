/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __SCREEN_H__
#define __SCREEN_H__


class Screen
{
    public:
        Screen(const char* cpName, int iWidth, int iHeight, bool bFullScreen);
        ~Screen();

        inline int getWidth() { return m_iWidth; }
        inline int getHeight() { return m_iHeight; }
        inline bool isFullScreen() { return m_bFullScreen; }

        void beginRender();
        void endRender();

    protected:
        int  m_iWidth;
        int  m_iHeight;
        bool  m_bFullScreen;
};


#endif
