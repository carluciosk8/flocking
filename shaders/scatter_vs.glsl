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


void main()
{
    //dist = length(gl_Vertex);
    //eyedir = normalize(gl_Vertex.xyz);
    //normalize(eyedir);
    gl_Position = ftransform();
    //color = L_in(s, s/8.0, t);
}
