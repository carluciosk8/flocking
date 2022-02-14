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
   m_kIndices(0),
   //m_oSun(0.0f, 0.0f, 800.0f),
   m_opShader(NULL)
{
}


Sky::~Sky()
{
    destroy();
}


void Sky::render()
{
    float3 vEye(0.0f, 300.0f, 0.0f);
        // Scattering multipliers.
        float fRayMult = m_oAtm.GetParam( eAtmBetaRayMultiplier );
        float fMieMult = m_oAtm.GetParam( eAtmBetaMieMultiplier );
        float3 vSunDir = m_oSun.GetDirection();
        ////////////hr = m_pEffect->SetValue(m_hLightDir, &vSunDir, 12);
        m_opShader->setUniform("LightDir", vSunDir);
        cout << "LightDir" << vSunDir << endl;


        float4 vSunColorIntensity = m_oSun.GetColorAndIntensity();
        //vSunColorIntensity.w = 9.677f - 352.95 * fMieMult;
        //vSunColorIntensity.w = 9.2f - 550.0f * fMieMult;
        //vSunColorIntensity.w = -9.2f;
        //m_oSun.SetSunIntensity(vSunColorIntensity.w);
        /////////////hr = m_pEffect->SetVector(m_hSunColorInt, &vSunColorIntensity);
        m_opShader->setUniform("vSunColorIntensity", vSunColorIntensity);
        cout << "vSunColorIntensity" << vSunColorIntensity << endl;


//        m_mtlSunClr.Emissive.r = vSunColorIntensity.x * 1.5f;
//        m_mtlSunClr.Emissive.g = vSunColorIntensity.y * 1.5f;
//        m_mtlSunClr.Emissive.b = vSunColorIntensity.z * 1.5f;
//        m_mtlSunClr.Ambient = m_mtlSunClr.Diffuse = m_mtlSunClr.Emissive;

        // calculate base height for density distance for a athmosphere
        // asuming a exponential density distribution dens = 1.2 * e^(h/8000)
        // h/8000 does not quite work, the eye is sensitive to log(intencity)
        // densbase = integrate [ alt to top ] top dens defined = 0.0f
        float4 vDensityAltBase;
        vDensityAltBase[0] = vEye.y / 1000.0f;
        vDensityAltBase[1] = powf(0.95f , vDensityAltBase[0]);
        vDensityAltBase[2] = 20000.0f * expf(-vEye.y / 10000.0f);
        vDensityAltBase[3] = 8000.0f * expf (-vEye.y / 20000.0f);
        //////////////////hr = m_pEffect->SetValue(m_hDensityDist, fDensityAltBase, 16);
        m_opShader->setUniform("vDensityAlt", vDensityAltBase);
        cout << "vDensityAlt" << vDensityAltBase << endl;


        float3 vBetaR , vBetaDashR , vBetaM , vBetaDashM , vBetaRM, vOneOverBetaRM;

        // Rayleigh
        vBetaR = m_oAtm.GetBetaRayleigh();
        vBetaR *= fRayMult;
        ////////////////m_pEffect->SetValue(m_hBetaRayleigh, &vBetaR, 12);
        m_opShader->setUniform("vBetaRayleigh", vBetaR);
        cout << "vBetaRayleigh" << vBetaR << endl;

        vBetaDashR = m_oAtm.GetBetaDashRayleigh();
        vBetaDashR *= fRayMult;
        ///////////////////hr = m_pEffect->SetValue (m_hBetaDashRayleigh, &vBetaDashR, 12);
        m_opShader->setUniform("vBetaDashRayleigh", vBetaDashR);
        cout << "vBetaDashRayleigh" << vBetaDashR << endl;

        // Mie
        vBetaM = m_oAtm.GetBetaMie();
        vBetaM *= fMieMult;
        /////////////////m_pEffect->SetValue (m_hBetaMie ,&vBetaM, 12);
        m_opShader->setUniform("vBetaMie", vBetaM);
        cout << "vBetaMie" << vBetaM << endl;

        vBetaDashM = m_oAtm.GetBetaDashMie();
        vBetaDashM *= fMieMult;
        /////////////////m_pEffect->SetValue(m_hBetaDashMie, &vBetaDashM, 12);
        m_opShader->setUniform("vBetaDashMie", vBetaDashM);
        cout << "vBetaDashMie" << vBetaDashM << endl;

        // Rayleigh + Mie
        vBetaRM = vBetaR + vBetaM;
        ////////////////m_pEffect->SetValue(m_hBetaRayleighMie, &vBetaRM, 12);
        m_opShader->setUniform("vBetaRayleighMie", vBetaRM);
        cout << "vBetaRayleighMie" << vBetaRM << endl;

        vOneOverBetaRM[0] = 1.0f /vBetaRM[0];
        vOneOverBetaRM[1] = 1.0f /vBetaRM[1];
        vOneOverBetaRM[2] = 1.0f /vBetaRM[2];
        //////////////////hr = m_pEffect->SetValue(m_hOneOverBetaRayleighMie, &vOneOverBetaRM, 12);
        m_opShader->setUniform("vOneOverBetaRM", vOneOverBetaRM);
        cout << "vOneOverBetaRM" << vOneOverBetaRM << endl;

        // each term (extinction, inscattering multiplier)
        float fIns = m_oAtm.GetParam(eAtmInscatteringMultiplier);

        // Henyey Greenstein's G value . and inscattering
        float g = m_oAtm.GetParam(eAtmHGg);
        //g = 0.293f + vEye.y * 1.18333e-5;
        //g = 0.193f + vEye.y * 1.03e-5;
        //g = 0.100f + vEye.y * 8.333e-6;
        //g = 0.163f + vEye.y * 1.393e-5;
        //g = 0.444f + vEye.y * 1.053e-5 - 5.984e-2 * m_oSun.GetSunTheta() - 3.521e-6 * m_oSun.GetSunTheta() * vEye.y;
        //float g2 = 0.100f + vEye.y * 1.11e-5 - 3.18e-2 * m_oSun.GetSunTheta() - 6.01e-6 * m_oSun.GetSunTheta() * vEye.y;
        float c = -0.076923f + 153.846f * fMieMult;
        //g = g + c*(g2 - g);
        //g = 0.250f + vEye.y * 1.3e-5 - 0.00e-2 * m_pSun->GetSunTheta() - 9.2e-6 * m_pSun->GetSunTheta() * vEye.y;
        float4 vG(1.0f-g*g, 1.0f+g*g, 2.0f*g, fIns);
        /////////////////m_pEffect->SetVector(m_hHenyeyGG, &vG);
        //m_oAtm.SetParam(eAtmHGg, g);
        m_opShader->setUniform("vHG", vG);
        cout << "vHG" << vG << endl;

        // Eye Position
        ////////////////m_pEffect->SetValue(m_hEyePosition, &vEye, 12);
        m_opShader->setUniform("vEyePos", vEye);
        cout << "vEyePos" << vEye << endl;

        // calculate the max light intensity
        float Ny = cosf(m_oSun.GetSunTheta());
        float k = powf(Ny, 0.3f);
        float a = ( 1.05f - powf(Ny, 0.3f) ) * 190000.0f;
        float Sr = a + k*(vDensityAltBase[2] - a);
        float Sm = a + k*(vDensityAltBase[3] - a);
        float betaRay0 = 2.0f;
        float betaMie0 = vG[0] / powf ( (vG.y - vG.z) , (3.0f/2.0f) );
        float3 vInMaxSun;
        for ( int i=0; i<3; i++)
        {
            vInMaxSun[i] = ( vBetaDashR[i] * betaRay0 + vBetaDashM[i] * betaMie0 ) *
                    vOneOverBetaRM[i] * vSunColorIntensity[i] *
                    (1.0f - expf(-(vBetaR[i]*Sr + vBetaM[i]*Sm) ) ) ;
        }
        Sr = Sm = 215000.0f;
        betaRay0 = 1.0f + Ny;
        betaMie0 = vG[0] / powf ( (vG.y - vG.z*Ny) , (3.0f/2.0f) );
        float3 vInMaxHoriz;
        for ( int i=0; i<3; i++)
        {
            vInMaxHoriz[i] = ( vBetaDashR[i] * betaRay0 + vBetaDashM[i] * betaMie0 ) *
                    vOneOverBetaRM[i] * vSunColorIntensity[i] *
                    (1.0f - expf(-(vBetaR[i]*Sr + vBetaM[i]*Sm) ) );
        }

        //D3DXVec3Maximize(&vInMaxSun, &vInMaxSun,&vInMaxHoriz);
        // float maxval = max( vInMaxSun.x, max(vInMaxSun.y, vInMaxSun.z) );
        // maxval = 1.0f / logf (maxval + 1.0f);
        // vG.w = maxval;
        // m_pEffect->SetVector(m_hHenyeyGG, &vG);
        for ( int i=0; i<3; i++)
        {
            vInMaxSun[i] = 1.0f / logf(1.0f + vInMaxHoriz[i]);
        }
        ////////////////////m_pEffect->SetValue(m_hToneMap, &vInMaxSun, 12);
        m_opShader->setUniform("vToneMap", vInMaxSun);
        cout << "vToneMap" << vInMaxSun << endl;

    // Set shader parameters
    //m_opShader->setUniform("vColor", float3(1.0f, 1.0f, 0.0f));

    TriMesh::render();
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
    m_kTexCoords[0].x = fPow(fabsf(m_kNormals[0].y), 0.3f);
    m_kTexCoords[0].y = (1.05f - m_kTexCoords[0].x ) * 190000.0f;

    m_kColors[0].x = fPow(fabsf(m_kNormals[0].y), 0.3f);
    m_kColors[0].y = (1.05f - m_kColors[0].x ) * 190000.0f;

    t += d;
    for (int ti=0; ti<iSub; ti++)
    {
        a = 0;
        for (int ai=0; ai<4*iSub; ai++)
        {
            int i = 4*iSub*ti + ai + 1;
            m_kVertices[i] = m_kNormals[i] = float3(fRad*sin(t)*cos(a), fRad*cos(t), fRad*sin(t)*sin(a));
            m_kNormals[i].normalize();
            m_kTexCoords[i].x = fPow(fabsf(m_kNormals[i].y), 0.3f);
            m_kTexCoords[i].y = (1.05f - m_kTexCoords[i].x ) * 190000.0f;
            m_kColors[i].x = fPow(fabsf(m_kNormals[i].y), 0.3f);
            m_kColors[i].y = (1.05f - m_kColors[i].x ) * 190000.0f;
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

    m_opShader = new ShaderState("shaders/sky_vs.glsl", "shaders/sky_fs.glsl");
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
