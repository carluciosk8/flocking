/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Trimesh.h"

#include <cstring>

#include <GL/glew.h>

TriMesh::TriMesh()
:
   m_fpVertexArray(0),
   m_fpNormalArray(0),
   m_fpColorArray(0),
   m_fpTxCrdArray(0),
   m_uipIndexArray(0),
   m_uiNumVerts(0),
   m_uiNumIndxs(0)
{}



void TriMesh::render()
{
   //glEnableClientState(GL_COLOR_ARRAY);
   glEnableClientState(GL_NORMAL_ARRAY);
   glEnableClientState(GL_VERTEX_ARRAY);
   glEnableClientState(GL_TEXTURE_COORD_ARRAY);

   //glColorPointer( 3, GL_FLOAT, 0, getColorPointer() );
   glNormalPointer( GL_FLOAT, 0, getNormalPointer() );
   glVertexPointer( 3, GL_FLOAT, 0, getVertexPointer() );
   glTexCoordPointer( 3, GL_FLOAT, 0, getTxCrdPointer() );

   glDrawElements(GL_TRIANGLES, indexArraySize(), GL_UNSIGNED_INT, getIndexPointer());

   //glDisableClientState(GL_COLOR_ARRAY);
   glDisableClientState(GL_NORMAL_ARRAY);
   glDisableClientState(GL_VERTEX_ARRAY);
   glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}



void TriMesh::create(float* fpVertices, float* fpNormals, float* fpColors,
                            float* fpTexCoords, unsigned int* uipIndexes,
                            unsigned int uiNumVerts, unsigned int uiNumIndxs)
{
   m_uiNumVerts = uiNumVerts;
   m_uiNumIndxs = uiNumIndxs;

   m_fpVertexArray = new float[uiNumVerts];
   m_fpNormalArray = new float[uiNumVerts];
   m_fpColorArray = new float[uiNumVerts];
   m_fpTxCrdArray = new float[uiNumVerts];
   m_uipIndexArray = new unsigned int[uiNumIndxs];

   memcpy(m_fpVertexArray, fpVertices, uiNumVerts*sizeof(float));
   memcpy(m_fpNormalArray, fpNormals, uiNumVerts*sizeof(float));
   memcpy(m_fpColorArray, fpColors, uiNumVerts*sizeof(float));
   memcpy(m_fpTxCrdArray, fpTexCoords, uiNumVerts*sizeof(float));
   memcpy(m_uipIndexArray, uipIndexes, uiNumIndxs*sizeof(unsigned int));
}



void TriMesh::destroy()
{
   delete[] m_fpVertexArray;
   delete[] m_fpNormalArray;
   delete[] m_fpColorArray;
   delete[] m_fpTxCrdArray;
   delete[] m_uipIndexArray;

   m_fpVertexArray = NULL;
   m_fpNormalArray = NULL;
   m_fpColorArray = NULL;
   m_fpTxCrdArray = NULL;
   m_uipIndexArray = NULL;

   m_uiNumVerts = 0;
   m_uiNumIndxs = 0;
}
