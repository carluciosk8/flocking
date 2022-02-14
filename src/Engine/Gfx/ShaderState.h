/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __SHADERSTATE_H__
#define __SHADERSTATE_H__


#include <GL/glew.h>
#include <string>

using std::string;

#include "RenderState.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"

class ShaderState : public RenderState
{
    public:
        ShaderState();
        ShaderState(const char* cpVS, const char* cpFS);
        virtual ~ShaderState();

        virtual void enable();
        virtual void disable();

        void loadVertexProgram(const char* cpFile);
        void loadFragmentProgram(const char* cpFile);
        void linkPrograms();

        void setUniform(const char* cpName, float fPar);
        void setUniform(const char* cpName, const float2& vrPar);
        void setUniform(const char* cpName, const float3& vrPar);
        void setUniform(const char* cpName, const float4& vrPar);


    protected:
        char* loadProgram(const char* cpFile);
        void printShaderInfoLog(GLuint obj);
        void printProgramInfoLog();

        const char* m_cpVertexShaderSource;
        const char* m_cpFragmentShaderSource;
        string  m_sVertexShaderSource;
        string  m_sFragmentShaderSource;

        GLuint  m_uiVertexShaderHnd;
        GLuint  m_uiFragmentShaderHnd;
        GLuint  m_uiProgramHnd;
};


#endif
