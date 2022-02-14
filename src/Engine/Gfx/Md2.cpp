/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#include "Md2.h"

//#ifdef _WIN32
//#include <windows.h>
//#endif
#include <GL/glew.h>
#include <SDL/SDL.h>

#include <cstdio>
#include <stdexcept>
#include <string>

using std::runtime_error;
using std::string;



bool CMd2::load(const char * szFilename)
{
    m_Timer.Init();
	unsigned char * ucpBuffer = 0;
	unsigned char * ucpPtr = 0;
	unsigned char * ucpTmpPtr = 0; 
	int iFileSize = 0;
	FILE * f;
	
	if ( !(f = fopen(szFilename, "rb")) )
	{
        throw runtime_error("CMd2::load() - Could not open MD2 file:" + string(szFilename));
		return false;
	}

	//check file size and read it all into the buffer
	int iStart = ftell(f);
	fseek(f, 0, SEEK_END);
	int iEnd = ftell(f);
	fseek(f, 0, SEEK_SET);
	iFileSize = iEnd - iStart;

	//Allocate memory for whole file
	ucpBuffer = new unsigned char[iFileSize];
	ucpPtr = ucpBuffer;

	if(!ucpBuffer)
	{
        throw runtime_error("CMd2::load() - Could not allocate memory for file:" + string(szFilename));
		return false;
	}

	//Load file into buffer
	if(fread(ucpBuffer, 1, iFileSize, f) != (unsigned)iFileSize)
	{
		delete [] ucpBuffer;
        throw runtime_error("CMd2::load() - Could not read from file:" + string(szFilename));
		return false;
	}

	//close the file, we don't need it anymore
	fclose(f);

	//get the header
	memcpy(&m_Head, ucpPtr, sizeof(SMD2Header));

	//make sure it is a valid MD2 file before we get going
	if(m_Head.m_iMagicNum != 844121161 || m_Head.m_iVersion != 8)
	{
		delete [] ucpBuffer;
        throw runtime_error("CMd2::load() - Is not a valid MD2 file:" + string(szFilename));
		return false;
	}
	
	ucpTmpPtr = ucpPtr;
	ucpTmpPtr += m_Head.m_iOffsetFrames;

	//read the frames
	m_pFrames = new SMD2Frame[m_Head.m_iNumFrames];
	
	for(int i = 0; i < m_Head.m_iNumFrames; i++)
	{
		float fScale[3];
		float fTrans[3];
		m_pFrames[i].m_pVerts = new SMD2Vert[m_Head.m_iNumVertices];
		//expand the verices
		memcpy(fScale, ucpTmpPtr, 12);
		memcpy(fTrans, ucpTmpPtr + 12, 12);
		memcpy(m_pFrames[i].m_caName, ucpTmpPtr + 24, 16);
		ucpTmpPtr += 40;
		for(int j = 0; j < m_Head.m_iNumVertices; j++)
		{
			//swap y and z coords to convert to the proper orientation on screen
			m_pFrames[i].m_pVerts[j].m_fVert[0] = ucpTmpPtr[0] * fScale[0] + fTrans[0];
			m_pFrames[i].m_pVerts[j].m_fVert[1] = ucpTmpPtr[2] * fScale[2] + fTrans[2];
			m_pFrames[i].m_pVerts[j].m_fVert[2] = ucpTmpPtr[1] * fScale[1] + fTrans[1];
			m_pFrames[i].m_pVerts[j].m_ucReserved = ucpTmpPtr[3];
			ucpTmpPtr += 4;
		}
		
	}

	//Read in the triangles
	ucpTmpPtr = ucpPtr;
	ucpTmpPtr += m_Head.m_iOffsetTriangles;
	m_pTriangles = new SMD2Tri[m_Head.m_iNumTriangles];
	memcpy(m_pTriangles, ucpTmpPtr, 12 * m_Head.m_iNumTriangles);

	//Read the U/V texture coords
	ucpTmpPtr = ucpPtr;
	ucpTmpPtr += m_Head.m_iOffsetTexCoords;
	m_pTexCoords = new SMD2TexCoord[m_Head.m_iNumTexCoords];
	short * sTexCoords = new short[m_Head.m_iNumTexCoords * 2];
	memcpy(sTexCoords, ucpTmpPtr, 4 * m_Head.m_iNumTexCoords);
	for(int i = 0; i < m_Head.m_iNumTexCoords; i++)
	{
		m_pTexCoords[i].m_fTex[0] = (float)sTexCoords[2*i] / m_Head.m_iSkinWidthPx;
		m_pTexCoords[i].m_fTex[1] = (float)sTexCoords[2*i+1] / m_Head.m_iSkinHeightPx;
	}
	delete [] sTexCoords;

	//Read the skin filenames
    if (m_Head.m_iNumSkins > 0)
    {
	    ucpTmpPtr = ucpPtr;
	    ucpTmpPtr += m_Head.m_iOffsetSkins;
	    m_pSkins = new SMD2Skin[m_Head.m_iNumSkins];
    	
	    //Load textures
	    for(int i = 0; i < m_Head.m_iNumSkins; i++)
	    {
            //hack off the leading parts and just get the filename
		    memcpy(m_pSkins[i].m_caSkin, ucpTmpPtr, 64);
		    char * szEnd = strrchr(m_pSkins[i].m_caSkin, '/');		
		    if(szEnd)
		    {
			    szEnd++;
			    strcpy(m_pSkins[i].m_caSkin, szEnd);
		    }
		    m_pSkins[i].m_Image.load(m_pSkins[i].m_caSkin);
		    ucpTmpPtr += 64;
            m_uiSkin = i;
	    }
    }

    m_pFaceNormals = new float3[m_Head.m_iNumTriangles];
    m_pVertexNormals = new float3[m_Head.m_iNumVertices];

    CalcNorms();
	delete [] ucpBuffer;

    return true;
}



void CMd2::render()
{
	if (m_bAnimate)
		animate(90.0f, m_iStartFrame, m_iEndFrame, true);
	else
	{
		if (m_bIsCustomSkin && m_pCustSkin)
			m_pCustSkin->enable();
		else if (m_pSkins)
			m_pSkins[m_uiSkin].m_Image.enable();

		glBegin(GL_TRIANGLES);
		{
			for(int x = 0; x < m_Head.m_iNumTriangles; x++)
			{
				glTexCoord2fv(m_pTexCoords[m_pTriangles[x].m_sTexIndices[0]].m_fTex);
				glNormal3fv(m_pVertexNormals[m_pTriangles[x].m_sVertIndices[0]]);
				glVertex3fv(m_pFrames[0].m_pVerts[m_pTriangles[x].m_sVertIndices[0]].m_fVert);

				glTexCoord2fv(m_pTexCoords[m_pTriangles[x].m_sTexIndices[1]].m_fTex);
				glNormal3fv(m_pVertexNormals[m_pTriangles[x].m_sVertIndices[1]]);
				glVertex3fv(m_pFrames[0].m_pVerts[m_pTriangles[x].m_sVertIndices[1]].m_fVert);

				glTexCoord2fv(m_pTexCoords[m_pTriangles[x].m_sTexIndices[2]].m_fTex);
				glNormal3fv(m_pVertexNormals[m_pTriangles[x].m_sVertIndices[2]]);
				glVertex3fv(m_pFrames[0].m_pVerts[m_pTriangles[x].m_sVertIndices[2]].m_fVert);
			}
		}
		glEnd();

		if (m_bIsCustomSkin && m_pCustSkin)
			m_pCustSkin->disable();
		else if (m_pSkins)
			m_pSkins[m_uiSkin].m_Image.disable();
	}
}



//-------------------------------------------------------------
//- Render
//- Renders a specific frame of the MD2 model
//-------------------------------------------------------------
/*
void CMd2::render(unsigned int uiFrame)
{
	if(!m_bIsCustomSkin)
		m_pSkins[m_uiSkin].m_Image.enable();
	else
		m_pCustSkin->enable();

	glBegin(GL_TRIANGLES);
    {
	    for(int x = 0; x < m_Head.m_iNumTriangles; x++)
	    {
		    glTexCoord2fv(m_pTexCoords[m_pTriangles[x].m_sTexIndices[0]].m_fTex);
		    glVertex3fv(m_pFrames[uiFrame].m_pVerts[m_pTriangles[x].m_sVertIndices[0]].m_fVert);
		    glTexCoord2fv(m_pTexCoords[m_pTriangles[x].m_sTexIndices[1]].m_fTex);
		    glVertex3fv(m_pFrames[uiFrame].m_pVerts[m_pTriangles[x].m_sVertIndices[1]].m_fVert);
		    glTexCoord2fv(m_pTexCoords[m_pTriangles[x].m_sTexIndices[2]].m_fTex);
		    glVertex3fv(m_pFrames[uiFrame].m_pVerts[m_pTriangles[x].m_sVertIndices[2]].m_fVert);
	    }
    }
	glEnd();

	if(!m_bIsCustomSkin)
		m_pSkins[m_uiSkin].m_Image.disable();
	else
		m_pCustSkin->disable();
}
*/



void CMd2::animate(float fSpeed, unsigned int uiStartFrame, unsigned int uiEndFrame, bool bLoop)
{
	//static unsigned int uiTotalFrames = 0;			//total number of frames
	//static unsigned int uiLastStart = 0, uiLastEnd = 0;	//last start/end parems passed to the function
	//static unsigned int uiLastFrame = 0;			//lastframe rendered
	//static unsigned int uiMSPerFrame = 0;			//number of milliseconds per frame
	//static float fLastInterp = 0;					//Last interpolation value

	//alloc a place to put the interpolated vertices
	if(!m_pVerts)
		m_pVerts = new SMD2Vert[m_Head.m_iNumVertices];

	//Prevent invalid frame counts
	if(uiEndFrame >= (unsigned)m_Head.m_iNumFrames)
		uiEndFrame = m_Head.m_iNumFrames - 1;
	if(uiStartFrame > (unsigned)m_Head.m_iNumFrames)
		uiStartFrame = 0;

	//avoid calculating everything every frame
	if(uiLastStart != uiStartFrame || uiLastEnd != uiEndFrame)
	{
		uiLastStart = uiStartFrame;
		uiLastEnd = uiEndFrame;
		if(uiStartFrame > uiEndFrame)
		{
			uiTotalFrames = m_Head.m_iNumFrames - uiStartFrame + uiEndFrame;
		}
		else
		{
			uiTotalFrames = uiEndFrame - uiStartFrame;
		}
	}
	uiMSPerFrame = (unsigned int)(1000.0f / fSpeed);
	
	//Calculate the next frame and the interpolation value
	float uiTime = m_Timer.GetMS();
	float fInterpValue = ( uiTime / uiMSPerFrame) + fLastInterp;
	fLastInterp = fInterpValue;

	//If the interpolation value is greater than 1, we must increment the frame counter
	while(fInterpValue > 1.0f)
	{
		uiLastFrame ++;
		if(uiLastFrame >= uiEndFrame)
		{
			uiLastFrame = uiStartFrame;
		}
		fInterpValue -= 1.0f;
		fLastInterp = 0.0f;
	}

	SMD2Frame* pCurFrame = &m_pFrames[uiLastFrame];
	SMD2Frame* pNextFrame = &m_pFrames[uiLastFrame+1];

	if(uiLastFrame == uiEndFrame-1)
		pNextFrame = &m_pFrames[uiStartFrame];
	
	//interpolate the vertices
	for(int x = 0; x < m_Head.m_iNumVertices; x++)
	{
		m_pVerts[x].m_fVert[0] = pCurFrame->m_pVerts[x].m_fVert[0] + (pNextFrame->m_pVerts[x].m_fVert[0] - pCurFrame->m_pVerts[x].m_fVert[0]) * fInterpValue;
		m_pVerts[x].m_fVert[1] = pCurFrame->m_pVerts[x].m_fVert[1] + (pNextFrame->m_pVerts[x].m_fVert[1] - pCurFrame->m_pVerts[x].m_fVert[1]) * fInterpValue;
		m_pVerts[x].m_fVert[2] = pCurFrame->m_pVerts[x].m_fVert[2] + (pNextFrame->m_pVerts[x].m_fVert[2] - pCurFrame->m_pVerts[x].m_fVert[2]) * fInterpValue;
	}

	//Render the new vertices
	if (m_bIsCustomSkin && m_pCustSkin)
		m_pCustSkin->enable();
	else if (m_pSkins)
		m_pSkins[m_uiSkin].m_Image.enable();

	glBegin(GL_TRIANGLES);
    {
	    for(int x = 0; x < m_Head.m_iNumTriangles; x++)
	    {
		    glTexCoord2fv(m_pTexCoords[m_pTriangles[x].m_sTexIndices[0]].m_fTex);
            glNormal3fv(m_pVertexNormals[m_pTriangles[x].m_sVertIndices[0]]);
		    glVertex3fv(m_pVerts[m_pTriangles[x].m_sVertIndices[0]].m_fVert);

		    glTexCoord2fv(m_pTexCoords[m_pTriangles[x].m_sTexIndices[1]].m_fTex);
            glNormal3fv(m_pVertexNormals[m_pTriangles[x].m_sVertIndices[1]]);
		    glVertex3fv(m_pVerts[m_pTriangles[x].m_sVertIndices[1]].m_fVert);

		    glTexCoord2fv(m_pTexCoords[m_pTriangles[x].m_sTexIndices[2]].m_fTex);
            glNormal3fv(m_pVertexNormals[m_pTriangles[x].m_sVertIndices[2]]);
		    glVertex3fv(m_pVerts[m_pTriangles[x].m_sVertIndices[2]].m_fVert);
	    }
    }
	glEnd();

	if (m_bIsCustomSkin && m_pCustSkin)
		m_pCustSkin->disable();
	else if (m_pSkins)
		m_pSkins[m_uiSkin].m_Image.disable();
}



/*
void CMd2::SetSkin(unsigned int uiSkin)
{
	m_uiSkin = uiSkin;
	m_bIsCustomSkin = false;
}
*/



void CMd2::SetSkin(TextureState* skin)
{
	m_pCustSkin = skin;
	m_bIsCustomSkin = true;
}



CMd2::CMd2()
{
    printf("Creating MD2 Model\n");
	m_pFrames = 0;
	m_pTriangles = 0;
	m_pTexCoords = 0;
	m_pSkins = 0;
	m_pVerts = 0;
	m_uiSkin = 0;
	m_bIsCustomSkin = false;
	m_pCustSkin = 0;
	m_bAnimate = false;
	m_Timer.Init();

	uiTotalFrames = 0;
	uiLastStart = 0, uiLastEnd = 0;
	uiLastFrame = 0;
	uiMSPerFrame = 0;
	fLastInterp = 0;

}



CMd2::CMd2(const char * szFile)
{
    printf("Creating MD2 Model\n");
	m_pFrames = 0;
	m_pTriangles = 0;
	m_pTexCoords = 0;
	m_pSkins = 0;
	m_bIsCustomSkin = false;
	m_pCustSkin = 0;
	m_bAnimate = false;
	m_pVerts = 0;
	m_uiSkin = 0;
	load(szFile);
	m_Timer.Init();

	uiTotalFrames = 0;
	uiLastStart = 0, uiLastEnd = 0;
	uiLastFrame = static_cast<unsigned int>(newRand(29));
	uiMSPerFrame = 0;
	fLastInterp = 0;
}



CMd2::~CMd2()
{
    printf("Deleting MD2 Model\n");

	if(m_pFrames)
	{
		delete [] m_pFrames;
		m_pFrames = NULL;
	}

	if(m_pTexCoords)
	{
		delete [] m_pTexCoords;
		m_pTexCoords = NULL;
	}

	if(m_pTriangles)
	{
		delete [] m_pTriangles;
		m_pTriangles = NULL;
	}

	if(m_pSkins)
	{
		delete [] m_pSkins;
		m_pSkins = NULL;
	}

	if(m_pVerts)
	{
		delete[] m_pVerts;
		m_pVerts = NULL;
	}

	if(m_pFaceNormals)
	{
		delete[] m_pFaceNormals;
		m_pFaceNormals = NULL;
	}

	if(m_pVertexNormals)
	{
		delete[] m_pVertexNormals;
		m_pVertexNormals = NULL;
	}
}



void CMd2::CalcNorms()
{
	//Calculate face normals first
	for(int x = 0; x < m_Head.m_iNumTriangles; x++)
	{
        float3 v0(m_pFrames[0].m_pVerts[m_pTriangles[x].m_sVertIndices[0]].m_fVert);
        float3 v1(m_pFrames[0].m_pVerts[m_pTriangles[x].m_sVertIndices[1]].m_fVert);
        float3 v2(m_pFrames[0].m_pVerts[m_pTriangles[x].m_sVertIndices[2]].m_fVert);
        CalcFaceNormal(m_pFaceNormals[x], v2, v1, v0);
	}
	//Calculate the vertex normals
	for(int x = 0; x < m_Head.m_iNumVertices; x++)
	{
		int iShared[20];  //Indices of shared faces
		int iNumShared = 0;   //Number of faces that share vertex
		
		//first find out which faces share the vertex
		for(int y = 0; y < m_Head.m_iNumTriangles; y++)
		{
			for(int z = 0; z < 3; z++)
			{
                if(m_pTriangles[y].m_sVertIndices[z] == x)
				{
					iShared[iNumShared] = y;
					iNumShared ++;
				}
			}
		}
		//Calculate a normal by averaging the face normals of the shared faces
        m_pVertexNormals[x] = float3::ZERO;
		for(int y = 0; y < iNumShared; y++)
		{
			m_pVertexNormals[x] += m_pFaceNormals[iShared[y]];
		}
		m_pVertexNormals[x] /= (float)iNumShared;
	}
}
