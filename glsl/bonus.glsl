const int Steps = 1000;
const float Epsilon = 0.01; // Marching epsilon
const float T=0.5;

const float rA=1.0; // Minimum ray marching distance from origin
const float rB=50.0; // Maximum
const float seaLevel = -0.4;
const float speed = 0.18; // Speed of water movement    
const vec3 sunPos = vec3(10, 1, 1);

// Transforms
vec3 rotateY(vec3 p, float a) {
   a = 10.0*a;
   return vec3(p.x*cos(a)-p.z*sin(a),p.y,p.x*sin(a)+p.z*cos(a));
}

// NOISE FUNCTIONS

// hash function for a 2D position
vec2 hash( vec2 p ) {
	p = vec2( dot(p,vec2(127.1,311.7)),
			  dot(p,vec2(269.5,183.3)) );

	return -1.0 + 2.0*fract(sin(p)*43758.5453123);
}

// simple noise with values between -1 and 1, and with a base spatial frequency of 1
float noise( in vec2 p ) {
    const float K1 = 0.366025404; // (sqrt(3)-1)/2;
    const float K2 = 0.211324865; // (3-sqrt(3))/6;

	vec2 i = floor( p + (p.x+p.y)*K1 );
	
    vec2 a = p - i + (i.x+i.y)*K2;
    vec2 o = step(a.yx,a.xy);    
    vec2 b = a - o + K2;
	vec2 c = a - 1.0 + 2.0*K2;

    vec3 h = max(0.5-vec3(dot(a,a), dot(b,b), dot(c,c) ), 0.0 );

	vec3 n = h*h*h*h*vec3( dot(a,hash(i+0.0)), dot(b,hash(i+o)), dot(c,hash(i+1.0)));

    return dot( n, vec3(70.0) );
}

float ridged(vec2 p) {
    return 1.0*(0.5-abs(0.5-noise(p)));
}

// combination of several noises at multiple frequencies
// amplitude : global amplitude
// fbase : base frequency (the lowest one)
// attenuation : coefficient in [0,1] that tells how amplitude is multiplied between each frequency
// noctave : number of octaves (the different frequencies)
float turbulence(in vec2 p, in float amplitude, in float fbase, in float attenuation, in int noctave) {
    int i;
    float res = .0;
    float f = fbase;
    for (i=0;i<noctave;i++) {
        res = res+amplitude*(ridged(f*p));
        amplitude = amplitude*attenuation;
        f = f*2.;
    }
    return res;
}

float WaterTurbulence(in vec2 p, in float amplitude, in float fbase, in float attenuation, in int noctave, in vec3 direction) {
    int i;
    float res = 0.0;
    float f = fbase;
    float s = speed;
    for (i=0;i<noctave;i++) {
        res = res + amplitude*noise(f*(p + iTime*s*direction.xz));
        amplitude = amplitude*attenuation;
        f = f*2.0;
        s *= -1.15;
    }
    return res;
}

// TERRAIN FUNCTIONS

float Terrain(vec3 p)
{
    float noiseValue = turbulence(p.xz, 2.5, 0.1, 0.46, 8);
    
    return noiseValue - p.y;
}

float Water(vec3 p)
{
    vec3 direction = vec3(1, 0, 0.5);
    float noiseValue = WaterTurbulence(p.xz, 0.04, 0.7, 0.4, 2, direction)/2.;
    direction = rotateY(direction, 1.);
    noiseValue += WaterTurbulence(p.xz, 0.04, 0.7, 0.4, 2, direction)/2.;
    return noiseValue + seaLevel - p.y;
}

// p : point
vec3 TerrainNormal(in vec3 p )
{
   float eps = 0.0001;
   vec3 n;
   float v = Terrain(p);
   n.x = Terrain( vec3(p.x+eps, p.y, p.z) ) - v;
   n.y = Terrain( vec3(p.x, p.y+eps, p.z) ) - v;
   n.z = Terrain( vec3(p.x, p.y, p.z+eps) ) - v;
   return normalize(n);
}

// Calculate object normal
// p : point
vec3 WaterNormal(in vec3 p )
{
   float eps = 0.0001;
   vec3 n;
   float v = Water(p);
   n.x = Water( vec3(p.x+eps, p.y, p.z) ) - v;
   n.y = Water( vec3(p.x, p.y+eps, p.z) ) - v;
   n.z = Water( vec3(p.x, p.y, p.z+eps) ) - v;
   return normalize(n);
}

// Trace ray using ray marching
// o : ray origin
// u : ray direction
// h : hit
// s : Number of steps
float Trace(vec3 o, vec3 u, out bool hitTerrain, out bool hitWater, out int s)
{
   hitTerrain = false;

   // Don't start at the origin
   // instead move a little bit forward
   float t=rA;

   for(int i=0; i<Steps; i++)
   {
      s=i;
      vec3 p = o+t*u;
      
      float vTerrain = Terrain(p);
      float vWater = Water(p);
      
           
      // Hit terrain 
      if (vTerrain > 0.0)
      {
         s=i;
         hitTerrain = true;
         break;
      }
      if (vWater > 0.0)
      {
          s=i;
          hitWater = true;
          break;
      }
      
      // Move along ray
      t += max(Epsilon, min(-vTerrain, -vWater)/2.0);  

      // Escape marched far away
      if (t>rB)
      {
         break;
      }
   }
   return t;
}

// Background color
vec3 background(vec3 rd)
{
   return mix(vec3(0.8, 0.8, 0.9), vec3(0.6, 0.9, 1.0), rd.y*1.0+0.25);
   //return mix(vec3(1, 1, 0), vec3(1, 0, 0)*0.9, rd.y*2.0+0.30);

}

// Shading and lighting
// p : point,
// n : normal at point
vec3 ShadeTerrain(vec3 p, vec3 n, int s)
{
   // point light
   const vec3 lightColor = vec3(1.0, 1.0, 1.0);
   
   vec3 ambientcolor = mix(vec3(0.6, 0.6, 0.1), vec3(0.05, 0.6, 0.05), p.y);

   
   // light direction
   vec3 l = normalize(sunPos - p);

   // Not even Phong shading, use weighted cosine instead for smooth transitions
   float diff = 0.5*(1.0+dot(n, l));
   
   // we mix ambient and diffuse components with an equal weight
   vec3 c =  0.5*ambientcolor + 0.5*diff*lightColor;
   return c;
}

vec3 ShadeWater(vec3 p, vec3 n, int s)
{
   // point light
   const vec3 lightColor = vec3(1.0, 1.0, 1.0);
   
   vec3 ambientcolor = vec3(0.1, 0.1, 1);

   
   // light direction
   vec3 l = normalize(sunPos - p);

   // Not even Phong shading, use weighted cosine instead for smooth transitions
   float diff = 1.5*(0.5+dot(-n, l));
   
   // we mix ambient and diffuse components with an equal weight
    vec3 specularColor = vec3(1.0, 1.0, 1.0);
    vec3 diffuseColor = 0.5*ambientcolor + 0.3*diff*lightColor;

   vec3 c =  dot(-n, l) < 0.75 ? diffuseColor : specularColor; //
   return c;
}






// MAIN

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
   vec2 pixel = (gl_FragCoord.xy / iResolution.xy)*2.0-1.0;

   // compute ray origin and direction
   float asp = iResolution.x / iResolution.y;
   vec3 rd = vec3(asp*pixel.x, pixel.y - 0.5, -3.0);
   vec3 ro = vec3(0.0, 5.0, 5.0);

   vec2 mouse = iMouse.xy / iResolution.xy;
   float a=-mouse.x;//iTime*0.25;
   rd.z = rd.z+2.0*mouse.y;
   rd = normalize(rd);
   ro = rotateY(ro, a);
   rd = rotateY(rd, a);

   // Trace ray
   bool hitTerrain, hitWater;

   // Number of steps
   int s;

   float t = Trace(ro, rd, hitTerrain, hitWater, s);
   vec3 pos=ro+t*rd;
   
   // Shade background
   vec3 rgb = background(rd);

   if (hitTerrain)
   {
      // Compute normal
      vec3 n = TerrainNormal(pos);

      // Shade object with light
      rgb = ShadeTerrain(pos, n, s);
   }
   
   else if (hitWater)
   {
       vec3 n = WaterNormal(pos);
       rgb = ShadeWater(pos, n, s);
   }

   fragColor=vec4(rgb, 1.0);
}

