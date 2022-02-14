/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Asteroid.h"

#include <iostream>

using std::cout;
using std::endl;


Asteroid::Asteroid()
:
   TriMesh(),
   m_fRadius(0),
   m_kVertices(0),
   m_kNormals(0),
   m_kColors(0),
   m_kIndices(0),
   m_uippEdjeMatrix(NULL)
{}


Asteroid::~Asteroid()
{
   destroy();
}



void Asteroid::destroy()
{
   m_fRadius = 0;
   m_kVertices.clear();
   m_kNormals.clear();
   m_kColors.clear();
   m_kIndices.clear();

   const static float log4=logf(4.0f);

   if ( m_uippEdjeMatrix )
   {
      for (int i=0; i<((logf((float)m_kIndices.size())/log4)-1); i++)
         delete[] m_uippEdjeMatrix[i];
      delete[] m_uippEdjeMatrix;
   }
   m_uippEdjeMatrix = NULL;

   TriMesh::destroy();
}


void Asteroid::generate(unsigned int uiSeed, float fRad, float fAmp, float fDec, unsigned int uiNumSub)
{
   const float a=0.57735026918963f;
   const float v=a*fRad;

   m_fRadius = fRad;
   m_kVertices = vector<float3>(4);
   m_kNormals = vector<float3>(4);
   m_kColors = vector<float3>(4);
   m_kTexCoords = vector<float3>(4);
   m_kIndices = vector<unsigned int>(12);

   m_kVertices[0].set(  v ,  v ,  v );
   m_kVertices[1].set( -v ,  v , -v );
   m_kVertices[2].set(  v , -v , -v );
   m_kVertices[3].set( -v , -v ,  v );

   m_kNormals[0].set(  a ,  a ,  a );
   m_kNormals[1].set( -a ,  a , -a );
   m_kNormals[2].set(  a , -a , -a );
   m_kNormals[3].set( -a , -a ,  a );

   m_kColors[0].set( 1.0 , 1.0 , 1.0 );
   m_kColors[1].set( 1.0 , 1.0 , 1.0 );
   m_kColors[2].set( 1.0 , 1.0 , 1.0 );
   m_kColors[3].set( 1.0 , 1.0 , 1.0 );

   m_kTexCoords[0].set( 1.0 , 1.0 , 0.0 );
   m_kTexCoords[1].set( 0.0 , 1.0 , 0.0 );
   m_kTexCoords[2].set( 1.0 , 0.0 , 0.0 );
   m_kTexCoords[3].set( 0.0 , 0.0 , 0.0 );

   m_kIndices[0]=0 ; m_kIndices[1]=1 ; m_kIndices[2]=2;
   m_kIndices[3]=0 ; m_kIndices[4]=1 ; m_kIndices[5]=3;
   m_kIndices[6]=0 ; m_kIndices[7]=2 ; m_kIndices[8]=3;
   m_kIndices[9]=1 ; m_kIndices[10]=2 ; m_kIndices[11]=3;

   unsigned int pow4 = 1<<(2*uiNumSub);
   m_uippEdjeMatrix = new unsigned int*[pow4];
   for (unsigned int i=0; i<pow4; i++)
      m_uippEdjeMatrix[i] = new unsigned int[pow4];

   for (unsigned int i=0; i<pow4; i++)
      for (unsigned int j=0; j<pow4; j++)
         m_uippEdjeMatrix[i][j]=0;

   srand(uiSeed);
   _subdivide(uiNumSub, fAmp, fDec);
}



void Asteroid::_subdivide(unsigned int uiNumSub, float fAmp, float fDec)
{
   int i0, i1, i2;
   int i01, i02, i12;
   unsigned int uiNumIndxs;
   float3 vrBarycenter;


   // iterative subdivision
   for (unsigned int sub=0; sub<uiNumSub; sub++ )
   {
      // calculate the barycenter of asteroid
	   vrBarycenter  = float3::ZERO;
      for (unsigned int i=0; i<m_kVertices.size(); i++)
         vrBarycenter  += m_kVertices[i];
      vrBarycenter  /= (float) m_kVertices.size();

      // for each triangle
      uiNumIndxs = m_kIndices.size();
      for (unsigned int tri=0; tri<uiNumIndxs; tri+=3)
      {
         i0 = m_kIndices[tri];
         i1 = m_kIndices[tri+1];
         i2 = m_kIndices[tri+2];

         i01 = _midPoint(i0, i1, fAmp, vrBarycenter );
         i02 = _midPoint(i0, i2, fAmp, vrBarycenter );
         i12 = _midPoint(i1, i2, fAmp, vrBarycenter );

         m_kIndices[tri] = i01;
         m_kIndices[tri+1] = i02;
         m_kIndices[tri+2] = i12;

         unsigned int ind[9] = { i0, i01, i02 ,
                                 i1, i01, i12 ,
                                 i2, i02, i12 };
         m_kIndices.insert(m_kIndices.end(), ind, ind+9);
      }
      fAmp *= fDec;
   }

   if (uiNumSub>0)
      for (unsigned int i=0; i<m_kVertices.size(); i++)
         m_kVertices[i] -= vrBarycenter ;


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
}



unsigned int Asteroid::_midPoint(unsigned int i1, unsigned int i2, float fAmp, float3 &vrBarycenter )
{
   unsigned int i = m_uippEdjeMatrix[i1][i2];

   // test if edje has already subdivided
   if ( i == 0 )
   {
      // Create new vertex
      float3 v;
      float d, l, r;

      // Calculate vertex position
      i = m_kVertices.size();
      v = (m_kVertices[i1]+m_kVertices[i2])/2.0f;
      r = (  (m_kVertices[i1]-vrBarycenter ).norm() +
             (m_kVertices[i2]-vrBarycenter ).norm() )/2.0f;
      l = fAmp*((m_kVertices[i1]-m_kVertices[i2]).norm());
      d = (float(rand())/RAND_MAX)-0.5f;
      v -= vrBarycenter;
      v.normalize();
      v *= (r+d*l/2.0f);
      v += vrBarycenter;
      m_kVertices.push_back(v);

      //if ( (r+d*l/2.0) > m_kSphere.getRadius() )
      //   m_kSphere.setRadius(r+d*l/2.0);

      // Calculate normal
      v.normalize();
      m_kNormals.push_back(v);

      // Calculate color
      m_kColors.push_back( (m_kColors[i1]+m_kColors[i2])/2.0 );

      // Calculate texture coord
      m_kTexCoords.push_back( (m_kTexCoords[i1]+m_kTexCoords[i2])/2.0 );

      // assign new vertex on edje matrix
      m_uippEdjeMatrix[i1][i2] = i;
      m_uippEdjeMatrix[i2][i1] = i;
   }
   return i;
}
