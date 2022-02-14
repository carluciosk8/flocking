/***************************************************************************
    Original code written in: May 2006    
    copyright: (C) Carlucio Santos Cordeiro
    Noise function by Ken Perlin
 ***************************************************************************/
#include "noise.h"



float Noise::noise2(float2 vec)
{
    int bx0, bx1, by0, by1, b00, b10, b01, b11;
    float  rx0, rx1, ry0, ry1, *q, sx, sy, a, b, t, u, v, result;
    int i, j;

//#ifdef UNLIMITED_NOISE_DOMAIN
//    filter_args(&vec.x, &vec.y, &vec.z);
//#endif

    setup(vec.x, bx0,bx1, rx0,rx1, t);
    setup(vec.y, by0,by1, ry0,ry1, t);

    i = p[ bx0 ];
    j = p[ bx1 ];

    b00 = p[ i + by0 ];
    b10 = p[ j + by0 ];
    b01 = p[ i + by1 ];
    b11 = p[ j + by1 ];

    sx = fSpline(rx0);
    sy = fSpline(ry0);

    q = g[ b00 ];       /* get random gradient */
    u = at2(rx0,ry0, q);   /* get weight on lo x side (lo y) */
    q = g[ b10 ];
    v = at2(rx1,ry0, q);   /* get weight on hi x side (lo y) */
    a = fLerp(u, v, sx); /* get value at distance sx between u & v */

                /* similarly at hi y... */
    q = g[ b01 ];   u = at2(rx0,ry1, q);
    q = g[ b11 ];   v = at2(rx1,ry1, q);
    b = fLerp(u, v, sx);

    result = 1.5f * fLerp(a, b, sy);  /* interpolate in y */

    return (result);
}


float Noise::noise3(float3 vec)
{
    int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
    float rx0, rx1, ry0, ry1, rz0, rz1, *q, sx, sy, sz, t;
    float a, b, c, d, u, v;
    int i, j;

//#ifdef UNLIMITED_NOISE_DOMAIN
//    filter_args(&vec.x, &vec.y, &vec.z);
//#endif

    setup(vec.x, bx0,bx1, rx0,rx1, t);
    setup(vec.y, by0,by1, ry0,ry1, t);
    setup(vec.z, bz0,bz1, rz0,rz1, t);

    i = p[ bx0 ];
    j = p[ bx1 ];

    b00 = p[ i + by0 ];
    b10 = p[ j + by0 ];
    b01 = p[ i + by1 ];
    b11 = p[ j + by1 ];

    sx = fSpline(rx0);
    sy = fSpline(ry0);
    sz = fSpline(rz0);

    q = g[ b00 + bz0 ]; u = at3(rx0,ry0,rz0, q);
    q = g[ b10 + bz0 ]; v = at3(rx1,ry0,rz0, q);
    a = fLerp(u, v, sx);

    q = g[ b01 + bz0 ]; u = at3(rx0,ry1,rz0, q);
    q = g[ b11 + bz0 ]; v = at3(rx1,ry1,rz0, q);
    b = fLerp(u, v, sx);

    c = fLerp(a, b, sy);     /* interpolate in y at lo z */

    q = g[ b00 + bz1 ]; u = at3(rx0,ry0,rz1, q);
    q = g[ b10 + bz1 ]; v = at3(rx1,ry0,rz1, q);
    a = fLerp(u, v, sx);

    q = g[ b01 + bz1 ]; u = at3(rx0,ry1,rz1, q);
    q = g[ b11 + bz1 ]; v = at3(rx1,ry1,rz1, q);
    b = fLerp(u, v, sx);

    d = fLerp(a, b, sy);     /* interpolate in y at hi z */

    return 1.5f * fLerp(c, d, sz);    /* interpolate in z */
}



int Noise::p[] =
{
    0,
    1,
    129,
    3,
    21,
    84,
    47,
    7,
    46,
    14,
    25,
    142,
    6,
    13,
    144,
    15,
    206,
    17,
    73,
    32,
    155,
    4,
    8,
    214,
    247,
    10,
    80,
    27,
    86,
    170,
    202,
    204,
    150,
    33,
    114,
    82,
    162,
    138,
    186,
    39,
    64,
    44,
    111,
    126,
    41,
    45,
    19,
    190,
    79,
    49,
    211,
    158,
    5,
    53,
    245,
    55,
    99,
    57,
    230,
    59,
    205,
    61,
    71,
    88,
    234,
    65,
    203,
    67,
    209,
    140,
    141,
    154,
    240,
    18,
    117,
    152,
    42,
    77,
    68,
    232,
    182,
    81,
    26,
    83,
    52,
    102,
    62,
    87,
    160,
    89,
    50,
    91,
    181,
    93,
    43,
    95,
    35,
    146,
    163,
    242,
    191,
    101,
    85,
    220,
    196,
    105,
    207,
    107,
    145,
    109,
    76,
    110,
    168,
    113,
    171,
    115,
    34,
    222,
    108,
    119,
    54,
    121,
    78,
    248,
    208,
    125,
    94,
    127,
    130,
    2,
    0,
    131,
    31,
    133,
    169,
    148,
    96,
    137,
    37,
    139,
    250,
    70,
    11,
    143,
    244,
    58,
    97,
    180,
    135,
    149,
    218,
    151,
    75,
    153,
    200,
    20,
    118,
    157,
    51,
    159,
    188,
    161,
    224,
    98,
    195,
    165,
    120,
    212,
    103,
    238,
    29,
    116,
    100,
    173,
    252,
    175,
    30,
    177,
    217,
    179,
    147,
    192,
    72,
    183,
    194,
    185,
    228,
    187,
    63,
    189,
    12,
    104,
    92,
    193,
    249,
    164,
    172,
    197,
    24,
    199,
    28,
    201,
    48,
    174,
    132,
    60,
    176,
    210,
    22,
    122,
    106,
    90,
    167,
    213,
    23,
    215,
    128,
    178,
    124,
    219,
    112,
    216,
    74,
    223,
    136,
    225,
    166,
    227,
    246,
    229,
    254,
    231,
    38,
    233,
    235,
    40,
    56,
    237,
    134,
    239,
    36,
    241,
    236,
    243,
    9,
    226,
    16,
    198,
    123,
    184,
    69,
    251,
    66,
    253,
    156,
    255,
    0,
    1,
    129,
    3,
    21,
    84,
    47,
    7,
    46,
    14,
    25,
    142,
    6,
    13,
    144,
    15,
    206,
    17,
    73,
    32,
    155,
    4,
    8,
    214,
    247,
    10,
    80,
    27,
    86,
    170,
    202,
    204,
    150,
    33,
    114,
    82,
    162,
    138,
    186,
    39,
    64,
    44,
    111,
    126,
    41,
    45,
    19,
    190,
    79,
    49,
    211,
    158,
    5,
    53,
    245,
    55,
    99,
    57,
    230,
    59,
    205,
    61,
    71,
    88,
    234,
    65,
    203,
    67,
    209,
    140,
    141,
    154,
    240,
    18,
    117,
    152,
    42,
    77,
    68,
    232,
    182,
    81,
    26,
    83,
    52,
    102,
    62,
    87,
    160,
    89,
    50,
    91,
    181,
    93,
    43,
    95,
    35,
    146,
    163,
    242,
    191,
    101,
    85,
    220,
    196,
    105,
    207,
    107,
    145,
    109,
    76,
    110,
    168,
    113,
    171,
    115,
    34,
    222,
    108,
    119,
    54,
    121,
    78,
    248,
    208,
    125,
    94,
    127,
    130,
    2,
    0,
    131,
    31,
    133,
    169,
    148,
    96,
    137,
    37,
    139,
    250,
    70,
    11,
    143,
    244,
    58,
    97,
    180,
    135,
    149,
    218,
    151,
    75,
    153,
    200,
    20,
    118,
    157,
    51,
    159,
    188,
    161,
    224,
    98,
    195,
    165,
    120,
    212,
    103,
    238,
    29,
    116,
    100,
    173,
    252,
    175,
    30,
    177,
    217,
    179,
    147,
    192,
    72,
    183,
    194,
    185,
    228,
    187,
    63,
    189,
    12,
    104,
    92,
    193,
    249,
    164,
    172,
    197,
    24,
    199,
    28,
    201,
    48,
    174,
    132,
    60,
    176,
    210,
    22,
    122,
    106,
    90,
    167,
    213,
    23,
    215,
    128,
    178,
    124,
    219,
    112,
    216,
    74,
    223,
    136,
    225,
    166,
    227,
    246,
    229,
    254,
    231,
    38,
    233,
    235,
    40,
    56,
    237,
    134,
    239,
    36,
    241,
    236,
    243,
    9,
    226,
    16,
    198,
    123,
    184,
    69,
    251,
    66,
    253,
    156,
    255,
    0,
    1,
};

float Noise::g[][3] =
{
    {0.881927, 0.00933256, -0.471294},
    {0.783613, 0.523784, 0.334067},
    {0.16021, -0.224294, 0.961262},
    {0.476773, -0.630021, 0.612994},
    {-0.299992, -0.549216, 0.779979},
    {-0.437603, -0.389943, 0.810215},
    {0.474441, -0.809644, -0.345517},
    {0.250258, 0.896758, 0.36496},
    {0.664083, -0.723553, 0.188322},
    {-0.955856, -0.00391744, -0.293808},
    {0.430173, -0.337663, -0.837219},
    {-0.608608, 0.107774, 0.786118},
    {-0.161776, 0.0276203, 0.986441},
    {-0.900782, 0.407496, -0.15013},
    {0.67719, -0.735235, -0.0290224},
    {0.435259, 0.383347, 0.814613},
    {0.990155, 0.0594093, -0.12674},
    {-0.0900124, 0.565078, -0.820113},
    {0.877974, 0.321742, -0.354462},
    {-0.292866, -0.348273, -0.89047},
    {-0.493484, -0.626647, 0.603148},
    {-0.018251, -0.748291, 0.66312},
    {0.442048, -0.191684, 0.876271},
    {-0.039175, -0.415255, -0.908861},
    {-0.375172, -0.875401, 0.304827},
    {0.816216, -0.575061, 0.0556511},
    {0.688177, 0.478367, -0.545506},
    {-0.519943, -0.0310413, 0.853637},
    {0.732517, 0.677232, -0.0691053},
    {-0.387999, -0.383872, 0.837913},
    {-0.495871, 0.602129, -0.625742},
    {-0.557869, -0.825864, -0.0820395},
    {-0.252615, 0.959939, -0.121255},
    {0.656728, -0.682583, 0.320607},
    {-0.0722408, 0.995318, -0.0642141},
    {0.0264206, 0.970958, 0.237786},
    {0.566363, -0.257857, -0.782779},
    {-0.79241, 0.608663, -0.0401947},
    {-0.61328, -0.789435, -0.026097},
    {0.621471, -0.777896, 0.0930093},
    {0.179964, 0.439912, -0.879824},
    {0.920163, -0.387437, 0.0565012},
    {0.731388, 0.427997, 0.530933},
    {0.696311, -0.575795, 0.428499},
    {0.714037, 0.409693, -0.567718},
    {-0.954945, 0.296734, 0.00539517},
    {-0.261215, 0.931668, -0.252508},
    {-0.0466522, 0.419869, 0.906385},
    {0.901551, -0.353311, -0.249754},
    {-0.0734223, -0.682827, -0.726881},
    {0.789875, 0.490128, -0.368608},
    {-0.842201, -0.191409, 0.504044},
    {0.768506, 0.286146, 0.572292},
    {0.659914, -0.611391, -0.436708},
    {0.637383, -0.174766, 0.750467},
    {0.0181811, -0.645428, -0.763605},
    {0.903195, 0.428914, -0.0164967},
    {-0.680163, 0.216645, -0.700316},
    {0.157334, 0.875823, 0.456267},
    {-0.725857, 0.488843, -0.483905},
    {-0.268821, -0.604847, -0.749597},
    {-0.206278, 0.56349, -0.799955},
    {-0.759064, -0.586905, 0.281715},
    {-0.626585, 0.779282, -0.0105308},
    {0.453898, 0.841373, 0.293373},
    {0.335068, -0.687101, -0.644687},
    {0.605501, -0.70011, 0.378438},
    {0.368652, 0.741971, 0.559978},
    {0.200715, -0.0821105, 0.976203},
    {0.870031, -0.487923, 0.0705431},
    {0.657558, -0.307665, -0.687721},
    {-0.803072, 0.317494, -0.504255},
    {-0.940811, -0.338894, 0.00505812},
    {0.945164, -0.219413, -0.241917},
    {0.543321, -0.628883, 0.556155},
    {0.117745, -0.781828, 0.612275},
    {-0.162865, 0.35381, -0.921029},
    {0.625338, 0.695941, -0.353013},
    {0.823315, 0.476656, 0.308141},
    {-0.586069, -0.138442, 0.798346},
    {-0.991332, 0.097024, -0.0885871},
    {-0.781887, -0.414443, 0.465714},
    {-0.370439, -0.928134, -0.0366369},
    {0.371806, 0.87668, -0.305273},
    {0.0246669, -0.999011, -0.0370004},
    {-0.777502, -0.622795, -0.0872707},
    {0.881495, -0.25652, -0.39644},
    {0.32106, 0.840871, -0.435724},
    {-0.908547, -0.204628, -0.364237},
    {-0.18656, -0.457919, -0.869198},
    {-0.0928068, 0.625437, -0.774735},
    {-0.80303, -0.499758, -0.324629},
    {0.467011, -0.862955, -0.192896},
    {-0.844156, 0.427559, 0.32341},
    {-0.366754, -0.171152, 0.914439},
    {-0.37027, -0.590118, -0.717398},
    {-0.327903, -0.595403, 0.733468},
    {0.0786493, 0.992192, -0.0967992},
    {0.470555, 0.796323, 0.380063},
    {-0.778758, -0.0450149, -0.625707},
    {0.287529, 0.406964, 0.867011},
    {-0.935035, -0.21864, 0.279115},
    {-0.333575, -0.942711, 0.00483442},
    {-0.487224, -0.861555, -0.142602},
    {0.524416, 0.348022, 0.77709},
    {-0.315749, -0.874779, 0.367511},
    {0.718447, 0.662256, -0.212724},
    {-0.108332, 0.526184, -0.843442},
    {-0.312189, 0.70359, 0.638357},
    {0.719518, -0.575614, -0.388539},
    {-0.116052, 0.98644, -0.116052},
    {0.835012, -0.0392024, -0.548834},
    {-0.263718, -0.61403, 0.743922},
    {0.662808, -0.14685, 0.734248},
    {-0.567505, 0.823282, -0.0119895},
    {0.0315202, -0.737572, -0.674532},
    {-0.463101, 0.767773, 0.44279},
    {0.760856, -0.502826, -0.4102},
    {-0.884402, 0.136062, -0.446453},
    {-0.820505, -0.0444609, 0.569908},
    {0.261755, 0.251285, -0.931848},
    {0.538347, 0.507289, -0.672934},
    {-0.833848, -0.489191, -0.255713},
    {-0.981969, 0.0892699, -0.166637},
    {0.567306, 0.669131, -0.480029},
    {0.471825, 0.845723, -0.249266},
    {0.178178, -0.0633521, 0.981957},
    {0.531368, -0.315365, 0.786252},
    {0.568053, 0.0272665, -0.82254},
    {-0.660161, 0.746849, -0.0800196},
    {-0.743197, 0.276539, 0.609249},
    {-0.121776, -0.748052, 0.652371},
    {0.90717, 0.415575, -0.0658838},
    {0.899211, -0.333993, -0.282609},
    {-0.929721, 0.164693, -0.329387},
    {-0.301401, -0.943517, -0.137596},
    {0.572063, -0.631428, 0.523491},
    {0.960138, 0.262223, 0.0968206},
    {0.956128, -0.0670967, -0.285161},
    {0.492877, -0.341223, -0.800399},
    {-0.0509833, -0.846322, -0.530226},
    {-0.119676, 0.977353, 0.174527},
    {0.579728, -0.614119, 0.535512},
    {-0.0165382, 0.70701, 0.70701},
    {0.776577, -0.496146, -0.388288},
    {-0.267511, -0.312852, -0.911351},
    {0.043586, -0.966156, -0.254251},
    {-0.619005, -0.706807, 0.342428},
    {0.34909, 0.934329, -0.0718715},
    {-0.207273, 0.288556, -0.934759},
    {0.191337, 0.569106, 0.799692},
    {0.706407, -0.307333, -0.637601},
    {-0.549731, -0.768827, 0.326652},
    {-0.597983, -0.776328, 0.199328},
    {0, 0.21279, 0.977098},
    {0.836218, 0.380099, -0.395303},
    {-0.347158, -0.586415, -0.731846},
    {-0.74361, 0.358621, -0.5643},
    {-0.119613, 0.967308, -0.223625},
    {0.521332, 0.392343, -0.757813},
    {0.333037, -0.636249, 0.695898},
    {-0.736632, -0.0687523, -0.67279},
    {-0.368305, -0.830733, 0.417413},
    {0.802572, 0.401286, 0.441415},
    {0.618643, -0.520566, -0.588466},
    {0.340475, -0.89686, 0.282345},
    {0.416618, 0.901255, -0.119034},
    {0.980928, -0.159461, -0.11114},
    {-0.874596, -0.477977, -0.0813578},
    {0.617716, 0.677112, -0.399932},
    {-0.719814, 0.482602, 0.498962},
    {0.312856, -0.483006, 0.817818},
    {0.319034, -0.0294493, 0.947286},
    {-0.691378, -0.550129, 0.468353},
    {-0.435125, 0.255549, -0.863343},
    {-0.484711, -0.803235, 0.346222},
    {0.170271, 0.887471, -0.428256},
    {0.112697, -0.798272, 0.59166},
    {-0.790477, -0.560622, 0.246674},
    {0.145604, -0.208006, -0.967229},
    {0.125644, -0.225292, -0.966156},
    {0.685839, 0.719918, -0.106497},
    {-0.501538, -0.3869, -0.773801},
    {0.416413, 0.904898, -0.0880874},
    {-0.615626, -0.619649, -0.486867},
    {0.669855, 0.525021, 0.525021},
    {-0.270705, 0.0887557, 0.958562},
    {-0.184426, -0.493999, 0.849678},
    {0.207925, -0.855237, -0.474696},
    {-0.35043, -0.133075, 0.927087},
    {-0.890682, -0.356273, 0.282411},
    {0.39093, 0.349045, 0.85167},
    {0.346808, -0.579477, 0.737516},
    {0.677666, 0.687347, 0.261386},
    {0.448941, 0.104405, -0.887441},
    {-0.769922, -0.558906, 0.307969},
    {0.863871, 0.497192, -0.0807937},
    {0.88277, -0.387558, -0.265549},
    {0.316139, 0.724484, -0.612519},
    {-0.156561, -0.305093, 0.939365},
    {-0.863919, 0.493668, -0.0996829},
    {-0.399274, 0.432948, 0.808169},
    {-0.201097, -0.827772, -0.523788},
    {0.649832, -0.69096, -0.31669},
    {0.58329, -0.762109, -0.281001},
    {-0.0146116, 0.0535757, -0.998457},
    {0.0301203, 0.85843, 0.512046},
    {0.122289, -0.778574, -0.615522},
    {-0.6378, -0.621855, -0.454432},
    {0.572703, -0.381802, 0.725423},
    {0.283725, -0.671761, -0.684278},
    {0.482124, 0.583624, 0.653405},
    {-0.464375, -0.883445, 0.0622942},
    {-0.343074, 0.810902, 0.474066},
    {0.362148, 0.354905, -0.861912},
    {0.245597, -0.30927, 0.918713},
    {0.404371, 0.269581, 0.873963},
    {0.104848, 0.986809, 0.123351},
    {0.600225, -0.104626, -0.792958},
    {-0.27876, -0.931313, 0.234412},
    {0, 0.987007, -0.160676},
    {-0.570647, -0.723605, 0.388276},
    {0.865457, 0.397092, -0.305455},
    {0.619109, 0.754539, -0.217656},
    {-0.112209, -0.0290913, -0.993259},
    {-0.481007, -0.15838, -0.862292},
    {-0.805298, 0.592131, -0.0296065},
    {-0.101503, -0.882635, 0.45897},
    {-0.84889, 0.523013, 0.0764403},
    {-0.0694843, -0.67499, 0.734548},
    {-0.0984886, 0.977007, 0.189098},
    {0.823002, 0.564805, 0.0605149},
    {-0.996435, -0.08052, 0.0251625},
    {0.319592, -0.834754, -0.448382},
    {0.798493, 0.550685, 0.243219},
    {-0.265283, -0.631625, 0.728474},
    {-0.678481, 0.325353, 0.658642},
    {0.729404, 0.070763, -0.680414},
    {-0.95973, 0.280536, -0.0147651},
    {-0.866431, -0.404334, -0.292936},
    {-0.528207, 0.803314, 0.275108},
    {-0.459883, 0.27593, -0.84402},
    {-0.164752, 0.804749, -0.570295},
    {0.616383, 0.273302, 0.738497},
    {-0.122193, 0.882944, -0.453297},
    {-0.643681, 0.760714, 0.083595},
    {-0.0738983, 0.468023, 0.880621},
    {0.314462, -0.612935, 0.724862},
    {-0.35677, 0.932466, 0.0567588},
    {0.511392, -0.146711, -0.846731},
    {-0.185801, 0.170318, 0.967714},
    {-0.171952, -0.96137, -0.214941},
    {-0.81662, 0.361197, 0.450188},
    {-0.0538588, 0.65977, 0.749535},
    {0.317011, -0.926956, -0.20064},
    {0.190026, 0.740102, -0.645089},
    {0.881927, 0.00933256, -0.471294},
    {0.783613, 0.523784, 0.334067},
    {0.16021, -0.224294, 0.961262},
    {0.476773, -0.630021, 0.612994},
    {-0.299992, -0.549216, 0.779979},
    {-0.437603, -0.389943, 0.810215},
    {0.474441, -0.809644, -0.345517},
    {0.250258, 0.896758, 0.36496},
    {0.664083, -0.723553, 0.188322},
    {-0.955856, -0.00391744, -0.293808},
    {0.430173, -0.337663, -0.837219},
    {-0.608608, 0.107774, 0.786118},
    {-0.161776, 0.0276203, 0.986441},
    {-0.900782, 0.407496, -0.15013},
    {0.67719, -0.735235, -0.0290224},
    {0.435259, 0.383347, 0.814613},
    {0.990155, 0.0594093, -0.12674},
    {-0.0900124, 0.565078, -0.820113},
    {0.877974, 0.321742, -0.354462},
    {-0.292866, -0.348273, -0.89047},
    {-0.493484, -0.626647, 0.603148},
    {-0.018251, -0.748291, 0.66312},
    {0.442048, -0.191684, 0.876271},
    {-0.039175, -0.415255, -0.908861},
    {-0.375172, -0.875401, 0.304827},
    {0.816216, -0.575061, 0.0556511},
    {0.688177, 0.478367, -0.545506},
    {-0.519943, -0.0310413, 0.853637},
    {0.732517, 0.677232, -0.0691053},
    {-0.387999, -0.383872, 0.837913},
    {-0.495871, 0.602129, -0.625742},
    {-0.557869, -0.825864, -0.0820395},
    {-0.252615, 0.959939, -0.121255},
    {0.656728, -0.682583, 0.320607},
    {-0.0722408, 0.995318, -0.0642141},
    {0.0264206, 0.970958, 0.237786},
    {0.566363, -0.257857, -0.782779},
    {-0.79241, 0.608663, -0.0401947},
    {-0.61328, -0.789435, -0.026097},
    {0.621471, -0.777896, 0.0930093},
    {0.179964, 0.439912, -0.879824},
    {0.920163, -0.387437, 0.0565012},
    {0.731388, 0.427997, 0.530933},
    {0.696311, -0.575795, 0.428499},
    {0.714037, 0.409693, -0.567718},
    {-0.954945, 0.296734, 0.00539517},
    {-0.261215, 0.931668, -0.252508},
    {-0.0466522, 0.419869, 0.906385},
    {0.901551, -0.353311, -0.249754},
    {-0.0734223, -0.682827, -0.726881},
    {0.789875, 0.490128, -0.368608},
    {-0.842201, -0.191409, 0.504044},
    {0.768506, 0.286146, 0.572292},
    {0.659914, -0.611391, -0.436708},
    {0.637383, -0.174766, 0.750467},
    {0.0181811, -0.645428, -0.763605},
    {0.903195, 0.428914, -0.0164967},
    {-0.680163, 0.216645, -0.700316},
    {0.157334, 0.875823, 0.456267},
    {-0.725857, 0.488843, -0.483905},
    {-0.268821, -0.604847, -0.749597},
    {-0.206278, 0.56349, -0.799955},
    {-0.759064, -0.586905, 0.281715},
    {-0.626585, 0.779282, -0.0105308},
    {0.453898, 0.841373, 0.293373},
    {0.335068, -0.687101, -0.644687},
    {0.605501, -0.70011, 0.378438},
    {0.368652, 0.741971, 0.559978},
    {0.200715, -0.0821105, 0.976203},
    {0.870031, -0.487923, 0.0705431},
    {0.657558, -0.307665, -0.687721},
    {-0.803072, 0.317494, -0.504255},
    {-0.940811, -0.338894, 0.00505812},
    {0.945164, -0.219413, -0.241917},
    {0.543321, -0.628883, 0.556155},
    {0.117745, -0.781828, 0.612275},
    {-0.162865, 0.35381, -0.921029},
    {0.625338, 0.695941, -0.353013},
    {0.823315, 0.476656, 0.308141},
    {-0.586069, -0.138442, 0.798346},
    {-0.991332, 0.097024, -0.0885871},
    {-0.781887, -0.414443, 0.465714},
    {-0.370439, -0.928134, -0.0366369},
    {0.371806, 0.87668, -0.305273},
    {0.0246669, -0.999011, -0.0370004},
    {-0.777502, -0.622795, -0.0872707},
    {0.881495, -0.25652, -0.39644},
    {0.32106, 0.840871, -0.435724},
    {-0.908547, -0.204628, -0.364237},
    {-0.18656, -0.457919, -0.869198},
    {-0.0928068, 0.625437, -0.774735},
    {-0.80303, -0.499758, -0.324629},
    {0.467011, -0.862955, -0.192896},
    {-0.844156, 0.427559, 0.32341},
    {-0.366754, -0.171152, 0.914439},
    {-0.37027, -0.590118, -0.717398},
    {-0.327903, -0.595403, 0.733468},
    {0.0786493, 0.992192, -0.0967992},
    {0.470555, 0.796323, 0.380063},
    {-0.778758, -0.0450149, -0.625707},
    {0.287529, 0.406964, 0.867011},
    {-0.935035, -0.21864, 0.279115},
    {-0.333575, -0.942711, 0.00483442},
    {-0.487224, -0.861555, -0.142602},
    {0.524416, 0.348022, 0.77709},
    {-0.315749, -0.874779, 0.367511},
    {0.718447, 0.662256, -0.212724},
    {-0.108332, 0.526184, -0.843442},
    {-0.312189, 0.70359, 0.638357},
    {0.719518, -0.575614, -0.388539},
    {-0.116052, 0.98644, -0.116052},
    {0.835012, -0.0392024, -0.548834},
    {-0.263718, -0.61403, 0.743922},
    {0.662808, -0.14685, 0.734248},
    {-0.567505, 0.823282, -0.0119895},
    {0.0315202, -0.737572, -0.674532},
    {-0.463101, 0.767773, 0.44279},
    {0.760856, -0.502826, -0.4102},
    {-0.884402, 0.136062, -0.446453},
    {-0.820505, -0.0444609, 0.569908},
    {0.261755, 0.251285, -0.931848},
    {0.538347, 0.507289, -0.672934},
    {-0.833848, -0.489191, -0.255713},
    {-0.981969, 0.0892699, -0.166637},
    {0.567306, 0.669131, -0.480029},
    {0.471825, 0.845723, -0.249266},
    {0.178178, -0.0633521, 0.981957},
    {0.531368, -0.315365, 0.786252},
    {0.568053, 0.0272665, -0.82254},
    {-0.660161, 0.746849, -0.0800196},
    {-0.743197, 0.276539, 0.609249},
    {-0.121776, -0.748052, 0.652371},
    {0.90717, 0.415575, -0.0658838},
    {0.899211, -0.333993, -0.282609},
    {-0.929721, 0.164693, -0.329387},
    {-0.301401, -0.943517, -0.137596},
    {0.572063, -0.631428, 0.523491},
    {0.960138, 0.262223, 0.0968206},
    {0.956128, -0.0670967, -0.285161},
    {0.492877, -0.341223, -0.800399},
    {-0.0509833, -0.846322, -0.530226},
    {-0.119676, 0.977353, 0.174527},
    {0.579728, -0.614119, 0.535512},
    {-0.0165382, 0.70701, 0.70701},
    {0.776577, -0.496146, -0.388288},
    {-0.267511, -0.312852, -0.911351},
    {0.043586, -0.966156, -0.254251},
    {-0.619005, -0.706807, 0.342428},
    {0.34909, 0.934329, -0.0718715},
    {-0.207273, 0.288556, -0.934759},
    {0.191337, 0.569106, 0.799692},
    {0.706407, -0.307333, -0.637601},
    {-0.549731, -0.768827, 0.326652},
    {-0.597983, -0.776328, 0.199328},
    {0, 0.21279, 0.977098},
    {0.836218, 0.380099, -0.395303},
    {-0.347158, -0.586415, -0.731846},
    {-0.74361, 0.358621, -0.5643},
    {-0.119613, 0.967308, -0.223625},
    {0.521332, 0.392343, -0.757813},
    {0.333037, -0.636249, 0.695898},
    {-0.736632, -0.0687523, -0.67279},
    {-0.368305, -0.830733, 0.417413},
    {0.802572, 0.401286, 0.441415},
    {0.618643, -0.520566, -0.588466},
    {0.340475, -0.89686, 0.282345},
    {0.416618, 0.901255, -0.119034},
    {0.980928, -0.159461, -0.11114},
    {-0.874596, -0.477977, -0.0813578},
    {0.617716, 0.677112, -0.399932},
    {-0.719814, 0.482602, 0.498962},
    {0.312856, -0.483006, 0.817818},
    {0.319034, -0.0294493, 0.947286},
    {-0.691378, -0.550129, 0.468353},
    {-0.435125, 0.255549, -0.863343},
    {-0.484711, -0.803235, 0.346222},
    {0.170271, 0.887471, -0.428256},
    {0.112697, -0.798272, 0.59166},
    {-0.790477, -0.560622, 0.246674},
    {0.145604, -0.208006, -0.967229},
    {0.125644, -0.225292, -0.966156},
    {0.685839, 0.719918, -0.106497},
    {-0.501538, -0.3869, -0.773801},
    {0.416413, 0.904898, -0.0880874},
    {-0.615626, -0.619649, -0.486867},
    {0.669855, 0.525021, 0.525021},
    {-0.270705, 0.0887557, 0.958562},
    {-0.184426, -0.493999, 0.849678},
    {0.207925, -0.855237, -0.474696},
    {-0.35043, -0.133075, 0.927087},
    {-0.890682, -0.356273, 0.282411},
    {0.39093, 0.349045, 0.85167},
    {0.346808, -0.579477, 0.737516},
    {0.677666, 0.687347, 0.261386},
    {0.448941, 0.104405, -0.887441},
    {-0.769922, -0.558906, 0.307969},
    {0.863871, 0.497192, -0.0807937},
    {0.88277, -0.387558, -0.265549},
    {0.316139, 0.724484, -0.612519},
    {-0.156561, -0.305093, 0.939365},
    {-0.863919, 0.493668, -0.0996829},
    {-0.399274, 0.432948, 0.808169},
    {-0.201097, -0.827772, -0.523788},
    {0.649832, -0.69096, -0.31669},
    {0.58329, -0.762109, -0.281001},
    {-0.0146116, 0.0535757, -0.998457},
    {0.0301203, 0.85843, 0.512046},
    {0.122289, -0.778574, -0.615522},
    {-0.6378, -0.621855, -0.454432},
    {0.572703, -0.381802, 0.725423},
    {0.283725, -0.671761, -0.684278},
    {0.482124, 0.583624, 0.653405},
    {-0.464375, -0.883445, 0.0622942},
    {-0.343074, 0.810902, 0.474066},
    {0.362148, 0.354905, -0.861912},
    {0.245597, -0.30927, 0.918713},
    {0.404371, 0.269581, 0.873963},
    {0.104848, 0.986809, 0.123351},
    {0.600225, -0.104626, -0.792958},
    {-0.27876, -0.931313, 0.234412},
    {0, 0.987007, -0.160676},
    {-0.570647, -0.723605, 0.388276},
    {0.865457, 0.397092, -0.305455},
    {0.619109, 0.754539, -0.217656},
    {-0.112209, -0.0290913, -0.993259},
    {-0.481007, -0.15838, -0.862292},
    {-0.805298, 0.592131, -0.0296065},
    {-0.101503, -0.882635, 0.45897},
    {-0.84889, 0.523013, 0.0764403},
    {-0.0694843, -0.67499, 0.734548},
    {-0.0984886, 0.977007, 0.189098},
    {0.823002, 0.564805, 0.0605149},
    {-0.996435, -0.08052, 0.0251625},
    {0.319592, -0.834754, -0.448382},
    {0.798493, 0.550685, 0.243219},
    {-0.265283, -0.631625, 0.728474},
    {-0.678481, 0.325353, 0.658642},
    {0.729404, 0.070763, -0.680414},
    {-0.95973, 0.280536, -0.0147651},
    {-0.866431, -0.404334, -0.292936},
    {-0.528207, 0.803314, 0.275108},
    {-0.459883, 0.27593, -0.84402},
    {-0.164752, 0.804749, -0.570295},
    {0.616383, 0.273302, 0.738497},
    {-0.122193, 0.882944, -0.453297},
    {-0.643681, 0.760714, 0.083595},
    {-0.0738983, 0.468023, 0.880621},
    {0.314462, -0.612935, 0.724862},
    {-0.35677, 0.932466, 0.0567588},
    {0.511392, -0.146711, -0.846731},
    {-0.185801, 0.170318, 0.967714},
    {-0.171952, -0.96137, -0.214941},
    {-0.81662, 0.361197, 0.450188},
    {-0.0538588, 0.65977, 0.749535},
    {0.317011, -0.926956, -0.20064},
    {0.190026, 0.740102, -0.645089},
    {0.881927, 0.00933256, -0.471294},
    {0.783613, 0.523784, 0.334067},
};
