/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __SKY_H__
#define __SKY_H__


#include <vector>

using std::vector;

#include "../Engine/Math/Vector3.h"
#include "../Engine/Gfx/Trimesh.h"

#include "Atmosphere.h"
#include "Sun.h"


class ShaderState;

class Sky : public TriMesh
{
    public:
        Sky();
        virtual ~Sky();

        virtual void render();

        void generate(int iSub, float fRad);
        void destroy();
        ShaderState* getShader() { return m_opShader; }

    protected:
        vector<float3> m_kVertices;
        vector<float3> m_kNormals;
        vector<float3> m_kColors;
        vector<float3> m_kTexCoords;
        vector<unsigned int> m_kIndices;

        Atmosphere  m_oAtm;
        Sun  m_oSun;
        ShaderState*  m_opShader;
};

#endif
