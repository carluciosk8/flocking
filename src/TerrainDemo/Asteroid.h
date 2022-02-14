/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include <vector>

using std::vector;

#include "../Engine/Math/Vector3.h"
#include "../Engine/Gfx/Trimesh.h"


class Asteroid : public TriMesh
{
   public:

      Asteroid();
	  virtual ~Asteroid();


      void destroy();
      void generate(unsigned int uiSeed = 1,
                     float fRad = 1.0,
                     float fAmp = 1.5,
                     float fDec = 0.5,
                     unsigned int uiNumSub = 3);


   protected:
      void _subdivide(unsigned int uiNumSub, float fAmp, float fDec);
      unsigned int _midPoint(unsigned int i1, unsigned int i2, float fAmp, float3 &kBarycenter);


      vector<float3> m_kVertices;  //!< Vertex buffer.
      vector<float3> m_kNormals;   //!< Normal buffer.
      vector<float3> m_kColors;    //!< Color buffer.
      vector<float3> m_kTexCoords; //!< Texture coordinate buffer.
      vector<unsigned int> m_kIndices;      //!< Index buffer.
      unsigned int **m_uippEdjeMatrix;      //!< Edje matrix, store idx. between two vs.
      float m_fRadius;              //!< Radius of the asteroid.
};


#endif
