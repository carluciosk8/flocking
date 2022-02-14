/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "ShaderState.h"

#include <stdexcept>
#include <fstream>
#include <iostream>
#include <cstring>

using std::runtime_error;
using std::ifstream;
using std::cout;
using std::endl;


ShaderState::ShaderState()
{
	if (! glewIsSupported("GL_VERSION_2_0"))
	{
		throw runtime_error("OpenGL 2.0 not supported");
	}
    else
    {
        printf("Ok. OpenGL 2.0 Supported\n");
    }

    if (! glewGetExtension("GL_ARB_shading_language_100"))
	{
		throw runtime_error("OpenGL Shading Language not supported");
	}
    else
    {
        printf("Ok. GLSL Supported\n");
    }

    //m_uiProgramHnd = glCreateProgram();
}



ShaderState::ShaderState(const char* cpVS, const char* cpFS)
{
    ShaderState();
	loadVertexProgram(cpVS);
	loadFragmentProgram(cpFS);
    linkPrograms();
}



ShaderState::~ShaderState()
{
    glDetachShader(m_uiProgramHnd, m_uiVertexShaderHnd);
    glDetachShader(m_uiProgramHnd, m_uiFragmentShaderHnd);
    glDeleteShader(m_uiVertexShaderHnd);
    glDeleteShader(m_uiFragmentShaderHnd);
    glDeleteProgram(m_uiProgramHnd);
}



void ShaderState::enable()
{
    glUseProgram(m_uiProgramHnd);
}



void ShaderState::disable()
{
    glUseProgram(0);
}



void ShaderState::loadVertexProgram(const char* cpFile)
{
	m_uiVertexShaderHnd = glCreateShader(GL_VERTEX_SHADER);

    m_cpVertexShaderSource = loadProgram(cpFile);
    cout << endl << endl << m_cpVertexShaderSource << endl << endl;
	GLint  vertCompiled;

    glShaderSource(m_uiVertexShaderHnd, 1, &m_cpVertexShaderSource, NULL);
	glCompileShader(m_uiVertexShaderHnd);
	glGetShaderiv(m_uiVertexShaderHnd, GL_COMPILE_STATUS, &vertCompiled);

    if (!vertCompiled)
    {
        printShaderInfoLog(m_uiVertexShaderHnd);
		throw runtime_error("Vertex Shader Compilation Error");
    }

    m_uiProgramHnd = glCreateProgram();
	glAttachShader(m_uiProgramHnd, m_uiVertexShaderHnd);
    delete[] m_cpVertexShaderSource;
}



void ShaderState::loadFragmentProgram(const char* cpFile)
{
	m_uiFragmentShaderHnd = glCreateShader(GL_FRAGMENT_SHADER);


    m_cpFragmentShaderSource = loadProgram(cpFile);
    cout << endl << endl << m_cpFragmentShaderSource << endl << endl;
	GLint  fragCompiled;

    glShaderSource(m_uiFragmentShaderHnd, 1, &m_cpFragmentShaderSource, NULL);
	glCompileShader(m_uiFragmentShaderHnd);
	glGetShaderiv(m_uiFragmentShaderHnd, GL_COMPILE_STATUS, &fragCompiled);

    if (!fragCompiled)
    {
        printShaderInfoLog(m_uiFragmentShaderHnd);
        throw runtime_error("Fragment Shader Compilation Error");
    }

	glAttachShader(m_uiProgramHnd, m_uiFragmentShaderHnd);
    delete[] m_cpFragmentShaderSource;
}



void ShaderState::linkPrograms()
{
	GLint  linked;

    glLinkProgram(m_uiProgramHnd);
	glGetProgramiv(m_uiProgramHnd, GL_LINK_STATUS, &linked);

	if (!linked)
		throw runtime_error("Shader Linker Error");
}



char* ShaderState::loadProgram(const char* cpFile)
{
    ifstream  oFileHnd(cpFile);
    string  sSource;


    if (! oFileHnd.is_open())
        throw runtime_error("Shader Source Error");

    while (! oFileHnd.eof())
    {
        string sLine;
        std::getline(oFileHnd, sLine);
        sSource += sLine + '\n';
    }
    oFileHnd.close();

    char* r = new char[sSource.length()+1];
    strcpy(r, sSource.c_str());
    r[sSource.length()]='\0';
    return r;
}



void ShaderState::printShaderInfoLog(GLuint obj)
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetShaderiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}



void ShaderState::printProgramInfoLog()
{
    int infologLength = 0;
    int charsWritten  = 0;
    char *infoLog;

    glGetProgramiv(m_uiProgramHnd, GL_INFO_LOG_LENGTH,&infologLength);

    if (infologLength > 0)
    {
        infoLog = (char *)malloc(infologLength);
        glGetProgramInfoLog(m_uiProgramHnd, infologLength, &charsWritten, infoLog);
        printf("%s\n",infoLog);
        free(infoLog);
    }
}



void ShaderState::setUniform(const char* cpName, float fPar)
{
    GLint loc = glGetUniformLocation(m_uiProgramHnd, cpName);
    //if (loc)
        glUniform1f(loc, fPar);
}



void ShaderState::setUniform(const char* cpName, const float2& vrPar)
{
    GLint loc = glGetUniformLocation(m_uiProgramHnd, cpName);
    //if (loc)
        glUniform2f(loc, vrPar.x, vrPar.y);
}



void ShaderState::setUniform(const char* cpName, const float3& vrPar)
{
    GLint loc = glGetUniformLocation(m_uiProgramHnd, cpName);
    //if (loc)
        glUniform3f(loc, vrPar.x, vrPar.y, vrPar.z);
}



void ShaderState::setUniform(const char* cpName, const float4& vrPar)
{
    GLint loc = glGetUniformLocation(m_uiProgramHnd, cpName);
    //if (loc)
        glUniform4f(loc, vrPar.x, vrPar.y, vrPar.z, vrPar.w);
}
