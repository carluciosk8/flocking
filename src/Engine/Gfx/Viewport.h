/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __VIEWPORT_H__
#define __VIEWPORT_H__


class Viewport
{
    public:
        Viewport(int iX, int iY, int iWidth, int iHeight);
        ~Viewport();

        inline int getX() const { return m_iX; }
        inline int getY() const { return m_iX; }
        inline int getWidth() const { return m_iWidth; }
        inline int getHeight() const { return m_iHeight; }

        void setViewport();


    protected:
        int m_iX;
        int m_iY;
        int m_iWidth;
        int m_iHeight;
};


#endif
