/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Sky.h"
#include "../Engine/Gfx/ShaderState.h"


#include <iostream>
#include <cstring>

using std::cout;
using std::endl;


Sky::Sky()
:
   TriMesh(),
   m_kVertices(0),
   m_kNormals(0),
   m_kColors(0),
   m_kIndices(0)
{}


Sky::~Sky()
{
    destroy();
}



void Sky::render()
{
    glDisable(GL_LIGHTING);
    TriMesh::render();
    glEnable(GL_LIGHTING);
}



void Sky::generate(int iSub, float fRad)
{
    float d = M_PI/(2.0f*static_cast<float>(iSub));
    float a = 0;
    float t = 0;

    m_kVertices = vector<float3>(4*iSub*(iSub + 1) + 1);
    m_kNormals = vector<float3>(4*iSub*(iSub + 1) + 1);
    m_kColors = vector<float3>(4*iSub*(iSub + 1) + 1);
    m_kTexCoords = vector<float3>(4*iSub*(iSub + 1) + 1);

    // Fill up vertex and normal buffer
    m_kVertices[0] = m_kNormals[0] = float3(fRad*sin(t)*cos(a), fRad*cos(t), fRad*sin(t)*sin(a));
    m_kNormals[0].normalize();
    m_kTexCoords[0].x = 0.5f;
    m_kTexCoords[0].y = 0.5f;
    t += d;
    for (int ti=0; ti<iSub; ti++)
    {
        a = 0;
        for (int ai=0; ai<4*iSub; ai++)
        {
            int i = 4*iSub*ti + ai + 1;
            m_kVertices[i] = m_kNormals[i] = float3(fRad*sin(t)*cos(a), fRad*cos(t), fRad*sin(t)*sin(a));
            m_kNormals[i].normalize();
            m_kTexCoords[i].x = 0.5f + 0.3f*t*cos(a);
            m_kTexCoords[i].y = 0.5f + 0.3f*t*sin(a);
            a += d;
        }
        t += d;
    }

    // Fill up index triangle buffer
    m_kIndices = vector<unsigned int>(3 * 4*iSub*(2*iSub + 1));
    int i=0;
    for (int ai=1; ai<4*iSub; ai++)
    {
        m_kIndices[i++] = 0;
        m_kIndices[i++] = ai;
        m_kIndices[i++] = ai+1;
    }
    m_kIndices[i++] = 0;
    m_kIndices[i++] = 4*iSub;
    m_kIndices[i++] = 1;

    for (int ti=0; ti<iSub-1; ti++)
    {
        int ai;
        for (ai=0; ai<4*iSub - 1; ai++)
        {
            m_kIndices[i++] = 4*iSub*ti + ai + 1;
            m_kIndices[i++] = 4*iSub*ti + ai + 2;
            m_kIndices[i++] = 4*iSub*(ti+1) + ai + 2;

            m_kIndices[i++] = 4*iSub*ti + ai + 1;
            m_kIndices[i++] = 4*iSub*(ti+1) + ai + 2;
            m_kIndices[i++] = 4*iSub*(ti+1) + ai + 1;
        }

        m_kIndices[i++] = 4*iSub*ti + ai + 1;
        m_kIndices[i++] = 4*iSub*ti + 1;
        m_kIndices[i++] = 4*iSub*(ti+1) + 1;

        m_kIndices[i++] = 4*iSub*ti + ai + 1;
        m_kIndices[i++] = 4*iSub*(ti+1) + 1;
        m_kIndices[i++] = 4*iSub*(ti+1) + ai + 1;
    }

    m_uiNumVerts = m_kVertices.size();
    m_uiNumIndxs = m_kIndices.size();

    m_fpVertexArray = new float[3*m_uiNumVerts];
    m_fpNormalArray = new float[3*m_uiNumVerts];
    m_fpColorArray = new float[3*m_uiNumVerts];
    m_fpTxCrdArray = new float[3*m_uiNumVerts];
    m_uipIndexArray = new unsigned int[m_uiNumIndxs];

    memcpy(m_fpVertexArray, &(m_kVertices[0]), 3*m_uiNumVerts*sizeof(float));
    memcpy(m_fpNormalArray, &(m_kNormals[0]), 3*m_uiNumVerts*sizeof(float));
    memcpy(m_fpColorArray, &(m_kColors[0]), 3*m_uiNumVerts*sizeof(float));
    memcpy(m_fpTxCrdArray, &(m_kTexCoords[0]), 3*m_uiNumVerts*sizeof(float));
    memcpy(m_uipIndexArray, &(m_kIndices[0]), m_uiNumIndxs*sizeof(unsigned int));

    //m_opShader = new ShaderState("shaders/sky_vs.glsl", "shaders/sky_fs.glsl");
}



void Sky::destroy()
{
    m_kVertices.clear();
    m_kNormals.clear();
    m_kColors.clear();
    m_kTexCoords.clear();
    m_kIndices.clear();

    TriMesh::destroy();
}
