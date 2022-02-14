/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __TERRAIN_H__
#define __TERRAIN_H__


#include "RenderableObject.h"
#include "../Math/Vector3.h"

class Terrain : public RenderableObject
{
    public:
        Terrain();
        virtual ~Terrain();

        virtual void render();

        void generate(int iHeightmapSize, float fCellSize);
        float getHeight(float fX, float fZ);
        float3 getNormal(float fX, float fZ);
        void calcNormals();


    protected:
        int  m_iHeightmapSize;
        float  m_fCellSize;
        float**  m_fppHeightmap;
        float3**  m_vppNormalmap;
};


#endif
