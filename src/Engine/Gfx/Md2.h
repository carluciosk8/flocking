/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
 ***************************************************************************/
#ifndef __MD2_H__
#define __MD2_H__


#include "Texture.h"
#include "RenderableObject.h"
#include "../Math/Vector3.h"
#include "CTimer.h"


class CMd2 : public RenderableObject
{
	public:
		//Set skin to one of the files specified in the md2 files itself
//		void SetSkin(unsigned int uiSkin);
		//Set skin to a different image
		void SetSkin(TextureState* skin);
	
		//Load the file
		bool load(const char * szFilename);
		
		//Render file at the initial position
		virtual void render();
		//Render the file at a certain frame
		//void render(unsigned int uiFrame);
	
		//Animate the md2 model (start and end frames of 0 and 0 will loop through the WHOLE model
		void animate(float fSpeed, unsigned int uiStartFrame, unsigned int uiEndFrame, bool bLoop);
		inline void setAnimateOn(bool on, int s, int e) { m_bAnimate = on; m_iStartFrame = s; m_iEndFrame = e; }
	
        void CalcNorms();

		//constructors/destructo
		CMd2();
		CMd2(const char* szFile);
		~CMd2();
	

    private:
        //-------------------------------------------------------------
        //- SMD2Header
        //- Header for all Md2 files, 
        struct SMD2Header
        {
            int m_iMagicNum; //Always IDP2 (844121161)
            int m_iVersion;  //8
            int m_iSkinWidthPx;  
            int m_iSkinHeightPx; 
            int m_iFrameSize; 
            int m_iNumSkins; 
            int m_iNumVertices; 
            int m_iNumTexCoords; 
            int m_iNumTriangles; 
            int m_iNumGLCommands; 
            int m_iNumFrames; 
            int m_iOffsetSkins; 
            int m_iOffsetTexCoords; 
            int m_iOffsetTriangles; 
            int m_iOffsetFrames; 
            int m_iOffsetGlCommands; 
            int m_iFileSize; 
        };


        //-------------------------------------------------------------
        //- SMD2Vert
        //- Vertex structure for MD2
        struct SMD2Vert
        {
	        float m_fVert[3];
	        unsigned char m_ucReserved;
        };


        //-------------------------------------------------------------
        //- SMD2Frame
        //- Frame information for the model file 
        struct SMD2Frame
        {
	        float m_fScale[3];
	        float m_fTrans[3];
	        char m_caName[16];
	        SMD2Vert * m_pVerts;

	        //Cleans up after itself
	        SMD2Frame()
	        {
		        m_pVerts = 0;
	        }

	        ~SMD2Frame()
	        {
		        if(m_pVerts)
			        delete [] m_pVerts;
	        }
        };


        //-------------------------------------------------------------
        //- SMD2Tri
        //- Triangle information for the MD2
        struct SMD2Tri
        {
	        unsigned short m_sVertIndices[3];
	        unsigned short m_sTexIndices[3];
        };


        //-------------------------------------------------------------
        //- SMD2TexCoord
        //- Texture coord information for the MD2
        struct SMD2TexCoord
        {
	        float m_fTex[2];
        };


        //-------------------------------------------------------------
        //- SMD2Skin
        //- Name of a single skin in the md2 file
        struct SMD2Skin
        {
	        char m_caSkin[64];      //filename
        	TextureState m_Image;   //Image file ready for texturing
        };


	private:
		CTimer m_Timer;
        //int m_iDelta;
		//file header information
		SMD2Header m_Head; 
		//Frame information
		SMD2Frame* m_pFrames;
		//Triangles
		SMD2Tri* m_pTriangles;
		//Texure coords
		SMD2TexCoord * m_pTexCoords;
		//Skin files
		SMD2Skin * m_pSkins;
		//Interpolated vertices
		SMD2Vert * m_pVerts;
		//Current skin
		unsigned int m_uiSkin;
		//Using a custom skin?
		bool m_bIsCustomSkin;
		//The custom skin
		TextureState* m_pCustSkin;
		bool m_bAnimate;
        int m_iStartFrame;
        int m_iEndFrame;

        float3* m_pFaceNormals;
        float3* m_pVertexNormals;

	    unsigned int uiTotalFrames;			//total number of frames
	    unsigned int uiLastStart, uiLastEnd;	//last start/end parems passed to the function
	    unsigned int uiLastFrame;			//lastframe rendered
	    unsigned int uiMSPerFrame;			//number of milliseconds per frame
	    float fLastInterp;					//Last interpolation value

    protected:
        inline void CalcFaceNormal(float3& n, const float3& p0, const float3& p1, const float3& p2)
        {
            float3 v0;
	        float3 v1;
            v0.sub(p1,p0);
            v1.sub(p2,p0);
            n.cross(v0,v1);
	        n.normalize();
        }

};



#endif //MD2_H
