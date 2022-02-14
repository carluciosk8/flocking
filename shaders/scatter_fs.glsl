//#define sqr(x)    (x)*(x)
//#define PI        3.14159365


void phase(in float cos_t, in float g, out float f_air, out float f_haze)
{
    //f_air = (3.0*(1.0 + sqr(cos_t)) / (16.0*PI));
    //f_air = 0.0596831*(1.0 + sqr(cos_t));
    //f_haze = ( sqr(1.0-g) / (4.0*PI*pow((1.0 + g*g - 2.0*g*cos_t), 1.5)) );
    //f_haze = (0.07957747 * sqr(1.0-g) * pow(1.0 + g*g - 2.0*g*cos_t, -1.5));
    f_air = 0.05968310*(1.0 + cos_t*cos_t);
    f_haze = ((1.0-g)*(1.0-g))*pow((1.0 + g*g - 2.0*g*cos_t), -1.5);
    //f_haze = 0.07957747*((1.0-g)*(1.0-g))*pow((1.0 + g*g - 2.0*g*cos_t), -1.5);
    //f_haze = ( (sqr(1.0-g)) / 4.0*PI*pow((1.0 + g*g - 2.0*g*cos_t), 1.5) );
}


vec3 L_in(float s_air, float s_haze, float cos_t, vec3 Esun)
{
    vec3 b_scAir = vec3(1111112.695, 1111112.118, 1111112.244);
    vec3 b_scHaze = vec3(2, 3, 4);
    vec3 b_exAir = b_scAir;
    vec3 b_exHaze = b_scHaze;// + vec3(0.00001, 0.00001, 0.00001);
    float g = 0.8;

    vec3 ext1 = exp(-(b_exAir + b_exHaze)*s_haze);
    vec3 ext2 = exp(-b_exAir*(s_air-s_haze));
    vec3 ext3 = exp(-b_scAir*s_air - b_scHaze*s_haze);

    float air;
    float haze;

    phase(cos_t, g, air, haze);
    b_scAir *= air;
    b_scHaze *= haze;

    vec3 one = vec3(1.0, 1.0, 1.0);
    vec3 E = Esun*( ((b_scAir+b_scHaze)/(b_exAir+b_exHaze))*(one - ext1) + (b_scAir/b_exAir)*(one-ext2)*ext1 );
    //vec3 E = Esun*((b_scAir+b_scHaze)/(b_exAir+b_exHaze))*(one - ext3);

    return (E);
}



//uniform vec3 E_sun;
//uniform vec3 sundir;

//varying float dist;
//varying vec3 eyedir;

void main()
{
    //normalize(eyedir);
    //vec3 view = normalize(eyedir);
    //float cos_t = dot(sundir, view);
    //vec3 colr = L_in(8400.0, 0.14881*dist, cos_t, E_sun);
    vec3 colr = L_in(2400.0, 250.0, 1.0, vec3(2.0, 2.0, 2.0));
    //vec3 colr = vec3(.0, 1.0, 1.0);
    gl_FragColor = vec4(colr, 1.0);
}
