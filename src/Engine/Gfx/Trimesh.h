/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __TRIMESH_H__
#define __TRIMESH_H__


#include "RenderableObject.h"


class TriMesh : public RenderableObject
{
   public:
      TriMesh();
      virtual ~TriMesh(){}

      virtual void render();


      void create(float* fpVertices, float* fpNormals, float* fpColors,
                  float* fpTexCoords, unsigned int* fpIndexes,
                  unsigned int uiNumVerts, unsigned int uiNumIndxs);
      void destroy();


      const float* getVertexPointer() const;
      const float* getNormalPointer() const;
      const float* getColorPointer() const;
      const float* getTxCrdPointer() const;
      const unsigned int* getIndexPointer() const;

      unsigned int vertexArraySize() const;
      unsigned int indexArraySize() const;


   protected:
      float *m_fpVertexArray;
      float *m_fpNormalArray;
      float *m_fpColorArray;
      float *m_fpTxCrdArray;
      unsigned int *m_uipIndexArray;
      unsigned int m_uiNumVerts;
      unsigned int m_uiNumIndxs;
};

#include "Trimesh.inl"


#endif
