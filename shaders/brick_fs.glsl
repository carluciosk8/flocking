varying vec3 lightDir,normal;
uniform sampler2D tex;

vec3 brick(vec2 p, 
           vec3 mortar_color, vec3 brick_color,
           float brick_width, float brick_height, float mortar_thickness)
{
   float bmw = brick_width + mortar_thickness;
   float bmh = brick_height + mortar_thickness;
   float mwf = 0.5*mortar_thickness/bmw;
   float mhf = 0.5*mortar_thickness/bmh;

   p.x = p.x / bmw;
   p.y = p.y / bmh;
   p.x += (mod(p.y*0.5, 1.0) > 0.5) ? 0.5 : 0.0;
   p.x -= floor(p.x);
   p.y -= floor(p.y);
   float w = (step(mwf, p.x) - step(1.0 - mwf, p.x));
   float h = (step(mhf, p.y) - step(1.0 - mhf, p.y));
   return mix(mortar_color, brick_color, w*h);
}


void main()
{
	vec3 ct,cf;
	vec4 texel;
	float intensity,at,af;

	intensity = max(dot(lightDir,normalize(normal)),0.0);

	cf = intensity * (gl_FrontMaterial.diffuse).rgb + 
					  gl_FrontMaterial.ambient.rgb;
	af = gl_FrontMaterial.diffuse.a;

	vec3 brick_color = vec3(0.5, 0.15, 0.14);
	vec3 mortar_color = vec3(0.5, 0.5, 0.5);
	texel.rgb = brick(gl_TexCoord[0].st, mortar_color, brick_color, 0.5, 0.3, 0.02);
	ct = texel.rgb;
	at = texel.a;

	gl_FragColor = vec4(ct * cf, at * af);	
}
