/*
#define PI        3.14159365
#define sqr(x)    x*x

varying float dist;



float f_air(float t)
{
     return (3.0*(1.0 + cos(t)*cos(t)) / (16.0*PI));
}

float f_haze(float t, float g)
{
    return ( ((1.0-g)*(1.0-g)) / 4.0*PI*pow((1.0 + g*g - 2.0*g*cos(t)), 1.5) );
}


void phase(in float t, in float g, out float f_air, out float f_haze)
{
    float cos_t = cos(t);
    f_air = 0.05968310*(1.0 + sqr(cos_t));
    f_haze = ( (sqr(1.0-g)) / 4.0*PI*pow((1.0 + g*g - 2.0*g*cos_t), 1.5) );
    f_haze = ( 0.07957747 * sqr(1.0-g) * pow((1.0 + g*g - 2.0*g*cos_t), -1.5) );
}


vec3 L_in(float s_air, float s_haze, float t)
{
    vec3 E_sun = vec3(2.0, 2.0, 2.0);
    vec3 b_scAir = vec3(0.00000695, 0.0000118, 0.0000244 );
    vec3 b_scHaze = vec3(0.00002, 0.00003, 0.00004);
    vec3 b_exAir = b_scAir;
    vec3 b_exHaze = vec3(0.000025, 0.000025, 0.000025);
    float g = -1.0;

    vec3 ext1 = exp(-(b_exAir + b_exHaze)*s_haze);
    vec3 ext2 = exp(-b_exAir*(s_air-s_haze));

    float air;
    float haze;

    phase(t, g, air, haze);
    b_scAir *= air;
    b_scHaze *= haze;

    E_sun *= ( ((b_scAir+b_scHaze)/(b_exAir+b_exHaze))*(vec3(1.0,1.0,1.0) - ext1)
               + (b_scAir/b_exAir)*(vec3(1.0,1.0,1.0)-ext2)*ext1 );

    return (E_sun);
}
*/

// Shader Parameters
//uniform vec3 eyepos;

// Interpolants to fragment
//varying float dist;
//varying vec3 eyedir;

/*
[1+cos^2(theta)] = Phase1(theta)
void phase(in float cos_theta, in float g, out float phase1, out float phase2)
{
    cos_theta = -cos_theta;

    Phase1(theta) = [1+cos^2(theta)]
    phase1 = 1.0 + cos_theta*cos_theta;

    Phase2(theta) = (1-g^2)/(1+g-2g*cos(theta))^(3/2)
    float den = sqrt(1.0 + g*g - 2.0*g*cos_theta);
    den = den * den * den;
    den = inversesqrt(den);
    phase2 =  (1.0 - g*g)/den;
}


uniform vec3  CamPos;

uniform vec3  Beta_1;
uniform vec3  BetaDash_1;
uniform vec3  Beta_2;
uniform vec3  BetaDash_2;
uniform float  hg;

uniform vec4  SunDir;
uniform vec4  SunColor;
uniform float  SunIntensity;

varying vec3  L_in;



void main()
{
    gl_Position = ftransform();

    vec3 Pos = gl_ModelViewMatrix * gl_Vertex.xyz;
    vec3 V = Pos - CamPos;
    vec3 V = (gl_ModelViewMatrix * gl_Vertex).xyz;
    vec3 D = (gl_ModelViewMatrix * SunDir).xyz;
    float s_1 = length(V);
    float s_2 = 0.14881*s_1;
    V = normalize(V);
    D = normalize(D);
    vec3 PV = (gl_ModelViewMatrix*gl_Vertex).xyz;
    float s_1 = abs(PV.z);
    float s_2 = 0.14881*s_1;

    float cos_t = dot(V, D);

    float Phase_1, Phase_2;
    phase(cos_t, hg, Phase_1, Phase_2);

    Inscattering (I) = (Beta'_1 * Phase_1(theta) + Beta'_2 * Phase_2(theta)) *
                       [1-exp(-Beta_1*s).exp(-Beta_2*s)] / (Beta_1 + Beta_2)
    vec3 I = (BetaDash_1*Phase_1 + BetaDash_2*Phase_2) * (1.0-exp(-(Beta_1*s_1 + Beta_2*s_2)))
                        / (Beta_1 + Beta_2);
    vec3 I = (BetaDash_1*Phase_1 + BetaDash_2*Phase_2) * (1.0-exp(-(Beta_1 + Beta_2)*s_2))
                       / (Beta_1 + Beta_2);
    I += (BetaDash_1*Phase_1) * (1.0-exp(-Beta_1*(s_1 - s_2))) * exp(-(Beta_1 + Beta_2)*s_1)
                       / (Beta_1);

    L_in = I * SunColor.rgb * 1.0;
    L_in = I;
}
*/



/*



// this is the effect file for the skydome
matrix WorldViewProj        : WORLDVIEWPROJECTION;
float3 LightDir             : LIGHTDIRECTION;
vector vSunColorIntensity   : SUNCOLORINTENSITY;
float3 vBetaRayleigh        : BETARAYLEIGH;
float3 vBetaDashRayleigh    : BETADASHRAYLEIGH;
float3 vBetaMie             : BETAMIE;
float3 vBetaDashMie         : BETADASHMIE;
float3 vBetaRayleighMie     : BETARAYLEIGHMIE;
float3 vOneOverBetaRM       : ONEOVERBETARAYLEIGHMIE;
float4 vHG                  : HENYEYGG;
float3 vEyePos              : EYEPOSITION;
float4 vDensityAlt          : DENSDIST;
float3 vToneMap             : TONEMAP;
float4 vConstants = {1.0 , -1.4426950 , 0.01 , 1000.0 } ; // constants

struct VS_OUTPUT
{
    float4 Pos  : POSITION;
    float4 Diff : COLOR0;
};

VS_OUTPUT VS( float3 vPos : POSITION, float3 Norm : NORMAL, float2 Tex : TEXCOORD)
{
    VS_OUTPUT Out = (VS_OUTPUT) 0 ;

    // transform
    Out.Pos = mul(float4(vPos, 1) , WorldViewProj);

    // determine angle between sun and view direction
    float4 viewAngle;
    viewAngle.x = dot(LightDir, Norm);
    viewAngle.y = ( viewAngle.x * viewAngle.x )/2 + 2;
    // viewAngle.y = ( viewAngle.x * viewAngle.x ) + 1;
    viewAngle.z = lerp (Tex.y , vDensityAlt.z , Tex.x );
    viewAngle.w = Tex.y ;
    viewAngle.w = lerp (viewAngle.w, vDensityAlt.w, Tex.x );

    // calculate extinction terms for inscatered extinction
    float3 extinction;
    extinction = vBetaRayleigh * viewAngle.z + vBetaMie*viewAngle.w;
    extinction = exp(-extinction);

    // calculate mie scatering term
    //Phase2 (theta) = (1 - g^2) / (1 + g^2 - 2*g*cos(theta))^(3/2)
    //vHG = [ 1 - g^2 , 1+g^2 , -2g , insc ]
    float4 phaseThetaMie;
    phaseThetaMie.x = vHG.z * viewAngle.x + vHG.y;
    phaseThetaMie.y = rsqrt(phaseThetaMie.x) ;
    phaseThetaMie.z = pow(phaseThetaMie.y , 3);
    phaseThetaMie.w = phaseThetaMie.z * vHG.x;

    // Inscattering ( I ) = ( Beta_R * Phase_R( the ta ) + Beta M * Phase M( the ta ) ) *
    // [1-exp(-Beta R*s ) . exp(-Beta M*s ) ] / ( Beta R + Beta M)
    float3  rayleigh;
    rayleigh = vBetaDashRayleigh * viewAngle.y;
    float3  mie;
    mie = vBetaDashMie * phaseThetaMie.w;
    float3  temp ;
    temp = vConstants.x - extinction;
    float3  inscatter; // I (inscattering)
    inscatter = (mie + rayleigh) * vOneOverBetaRM;
    inscatter *= temp;
    inscatter *= vSunColorIntensity.xyz;
    inscatter *= vSunColorIntensity.w;

    // color
    Out.Diff.xyz = inscatter;
    Out.Diff.z += 0.15;
    Out.Diff.w = 1.0;
    return Out;
}


// PS
f l o a t 4 PS(VS OUTPUT In ) : COLOR
{
    f l o a t 4 Color = ( f l o a t 4 ) 0 ;
    f l o a t 4 Temp = ( f l o a t 4 ) 0 ;
    Color = In . Di f f ;
    r e turn Color ;
}
//Technique T0 , r ende r ing the skydome with a cons tant c o l o r
// in a s i n g l e pass , no s c a t e r ing , no shade r s
t e chnique T0
{
    pas s P0
    {
        f v f = XYZ | Normal | Tex1 ;
        // Fi l lMode = WIREFRAME;
        VertexShader = compi le v s 1 1 VS( ) ;
        Pixe lShade r = compi le ps 1 1 PS( ) ;
        Light ing = FALSE;
        Zwr i teEnable = FALSE;
        CullMode = NONE;
    }
}
*/






//matrix WorldViewProj        : WORLDVIEWPROJECTION;
uniform vec3 LightDir;
uniform vec4 vSunColorIntensity;// = vec4(1.0,1.0,0.5,50.0);
uniform vec3 vBetaRayleigh;
uniform vec3 vBetaDashRayleigh;
uniform vec3 vBetaMie;
uniform vec3 vBetaDashMie;
uniform vec3 vBetaRayleighMie;
uniform vec3 vOneOverBetaRM;
uniform vec4 vHG;
uniform vec3 vEyePos;
uniform vec4 vDensityAlt;
uniform vec3 vToneMap;

const vec4 vConstants = vec4(1.0 , -1.4426950 , 0.01 , 1000.0); // constants
//uniform vec4 vConstants; // constants


//varying vec4 Pos;
varying vec4 Diff;

void main()
{
    // transform
    gl_Position = ftransform();
    // determine angle between sun and view direction
    vec4 viewAngle;
    viewAngle.x = dot(LightDir, gl_Normal);
    viewAngle.y = ( viewAngle.x * viewAngle.x )/2.0 + 2.0;
    // viewAngle.y = ( viewAngle.x * viewAngle.x ) + 1;
    viewAngle.z = mix(gl_Color.y , vDensityAlt.z , gl_Color.x );
    viewAngle.w = gl_Color.y ;
    viewAngle.w = mix(viewAngle.w, vDensityAlt.w, gl_Color.x );

    // calculate extinction terms for inscatered extinction
    vec3 extinction;
    extinction = vBetaRayleigh * viewAngle.z + vBetaMie*viewAngle.w;
    extinction = exp(-extinction);

    // calculate mie scatering term
    //Phase2 (theta) = (1 - g^2) / (1 + g^2 - 2*g*cos(theta))^(3/2)
    //vHG = [ 1 - g^2 , 1+g^2 , -2g , insc ]
    vec4 phaseThetaMie;
    phaseThetaMie.x = vHG.z * viewAngle.x + vHG.y;
    phaseThetaMie.y = 1.0/sqrt(phaseThetaMie.x);
    phaseThetaMie.z = phaseThetaMie.y*phaseThetaMie.y*phaseThetaMie.y;//pow(phaseThetaMie.y, 3.0);
    phaseThetaMie.w = phaseThetaMie.z * vHG.x;

    // Inscattering ( I ) = ( Beta_R * Phase_R( the ta ) + Beta M * Phase M( the ta ) ) *
    // [1-exp(-Beta R*s ) . exp(-Beta M*s ) ] / ( Beta R + Beta M)
    vec3  rayleigh;
    rayleigh = vBetaDashRayleigh * viewAngle.y;
    vec3  mie;
    mie = vBetaDashMie * phaseThetaMie.w;
    vec3  temp ;
    temp = 1.0 - extinction;
    vec3  inscatter; // I (inscattering)
    inscatter = (mie + rayleigh) * vOneOverBetaRM;
    inscatter *= temp;
    inscatter *= vSunColorIntensity.xyz;
    inscatter *= vSunColorIntensity.w;

    // color
    Diff.xyz = inscatter;
    Diff.z += 0.15;
    Diff.w = 1.0;
}
