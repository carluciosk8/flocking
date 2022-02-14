/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Terrain.h"
#include "../Math/multifractal.h"

#include <GL/glew.h>

#include <cstdio>
#include <cmath>
#include <ctime>


Terrain::Terrain()
: m_iHeightmapSize(0),
  m_fCellSize(0)
{}



Terrain::~Terrain()
{
    for(int i=0;i<m_iHeightmapSize;i++)
    {
        delete[] m_fppHeightmap[i];
        delete[] m_vppNormalmap[i];
    }
    delete[] m_fppHeightmap;
    delete[] m_vppNormalmap;
}



void Terrain::render()
{
    for(int z=0 ; z<m_iHeightmapSize-1 ; z++)
    {
       	glBegin(GL_TRIANGLE_STRIP);
        glColor3f(1.0f, 1.0f, 1.0f);
        for(int x=0 ; x<m_iHeightmapSize ; x++)
        {
            float t = m_iHeightmapSize*0.5f;
            glTexCoord2f(.040f*float(x), .040f*float(z));
            glNormal3f(m_vppNormalmap[z][x].x, -m_vppNormalmap[z][x].y, m_vppNormalmap[z][x].z);
       	    glVertex3f((x - t)*m_fCellSize, m_fppHeightmap[z][x] , (z - t)*m_fCellSize);

            glTexCoord2f(.040f*float(x), .040f*float(z+1));
            glNormal3f(m_vppNormalmap[z+1][x].x, -m_vppNormalmap[z+1][x].y, m_vppNormalmap[z+1][x].z);
       	    glVertex3f((x - t)*m_fCellSize, m_fppHeightmap[z+1][x] , (z + 1 - t)*m_fCellSize);
        }
        glEnd();
    }
}



void Terrain::generate(int iHeightmapSize, float fCellSize)
{
    m_iHeightmapSize = iHeightmapSize;
    m_fCellSize = fCellSize;
    m_fppHeightmap = new float*[m_iHeightmapSize];
    m_vppNormalmap = new float3*[m_iHeightmapSize];
    for(int i=0;i<m_iHeightmapSize;i++)
    {
        m_fppHeightmap[i] = new float[m_iHeightmapSize];
        m_vppNormalmap[i] = new float3[m_iHeightmapSize];
    }


    srand( time(0) );

    long startx= rand()%100;
    long starty= rand()%100;
    float h=1.5f;
    float lac=0.25f;
    float oct=4.0f;
    float offset=2.0f;
    float thresh=2.0f;
//     long startx= 0;
//     long starty= 0;
//     float h=0.0f;
//     float lac=0.0f;
//     float oct=0.0f;
//     float offset=0.0f;
//     float thresh=0.0f;

    for(int y=0;y<m_iHeightmapSize;y++)
        for(int x=0;x<m_iHeightmapSize;x++)
            m_fppHeightmap[y][x] = RidgedMultifractal(float3(startx+x,starty+y,0), h, lac, oct, offset, thresh);

    calcNormals();
}



float Terrain::getHeight(float fX, float fZ)
{
    float fTerrainSize = float(m_iHeightmapSize)*m_fCellSize*0.5f;

    if ( fX > -fTerrainSize && fX < fTerrainSize && fZ > -fTerrainSize && fZ < fTerrainSize)
    {
        int xHM = int(floor(fX/m_fCellSize)) + m_iHeightmapSize/2;
        int zHM = int(floor(fZ/m_fCellSize)) + m_iHeightmapSize/2;

        float dx = fX/m_fCellSize - (xHM - m_iHeightmapSize*0.5f);
        float dz = fZ/m_fCellSize - (zHM - m_iHeightmapSize*0.5f);

        float y1 = fLerp(m_fppHeightmap[zHM][xHM], m_fppHeightmap[zHM][xHM+1], dx);
        float y2 = fLerp(m_fppHeightmap[zHM+1][xHM], m_fppHeightmap[zHM+1][xHM+1], dx);
        return fLerp(y1, y2, dz);
    }
    else
    {
        return 0.0f;
    }
}



float3 Terrain::getNormal(float fX, float fZ)
{
    float fTerrainSize = float(m_iHeightmapSize)*m_fCellSize*0.5f;

    if ( fX > -fTerrainSize && fX < fTerrainSize && fZ > -fTerrainSize && fZ < fTerrainSize)
    {
        int xHM = int(floor(fX/m_fCellSize)) + m_iHeightmapSize/2;
        int zHM = int(floor(fZ/m_fCellSize)) + m_iHeightmapSize/2;

        float dx = fX/m_fCellSize - (xHM - m_iHeightmapSize*0.5f);
        float dz = fZ/m_fCellSize - (zHM - m_iHeightmapSize*0.5f);

        float3 y1 = fLerp(m_vppNormalmap[zHM][xHM], m_vppNormalmap[zHM][xHM+1], dx);
        float3 y2 = fLerp(m_vppNormalmap[zHM+1][xHM], m_vppNormalmap[zHM+1][xHM+1], dx);
        return fLerp(y1, y2, dz);
    }
    else
    {
        return float3::ZERO;
    }
}



void Terrain::calcNormals()
{
	for (int x=1;x<m_iHeightmapSize-1;x++)
    {
	    for (int z=1;z<m_iHeightmapSize-1;z++)
	    {
		    m_vppNormalmap[z][x].x = m_fppHeightmap[z][x+1] - m_fppHeightmap[z][x-1];
		    m_vppNormalmap[z][x].y = 2.0f*m_fCellSize;
		    m_vppNormalmap[z][x].z = m_fppHeightmap[z+1][x] - m_fppHeightmap[z-1][x];
            m_vppNormalmap[z][x].normalize();
	    }
    }
}
