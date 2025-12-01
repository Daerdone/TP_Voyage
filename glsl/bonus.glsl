#iChannel0 "file://water_normal_map.png"
#iChannel1 "self" // permet de lire les pixels de l'image précédente, pour y stocker la position et l'orientation de la caméra
#iKeyboard

const float Epsilon = 0.005;

const float minRenderDistance=1.0;
const float maxRenderDistance=35.0; // = render distance
const float minShadowDistance=0.05;
const float maxShadowDistance=10.0; // = max distance between an object and its shadow
const float seaLevel = -0.20;
const float WaterSpeed = 0.18;
vec3 sunPos = normalize(vec3(0, 3, 5));

const float moveSpeed = 3.0;
const float mouseSensitivity = 3.0;

const float sunAngle = 0.001;


vec3 sampleWaterNormalMap(vec2 uv)
{
    vec3 n = texture(iChannel0, uv).xyz * 2.0 - 1.0;
    return vec3(n.x, n.z, n.y);
}

vec3 rotateY(vec3 p, float a) {
    a = 10.0*a;
    return vec3(p.x*cos(a)-p.z*sin(a),p.y,p.x*sin(a)+p.z*cos(a));
}

vec3 rotateX(vec3 p, float a) {
    return vec3(p.x, p.y*cos(a)-p.z*sin(a), p.y*sin(a)+p.z*cos(a));
}

mat3 lookAtMatrix(float yaw, float pitch) {
    float cy = cos(yaw), sy = sin(yaw);
    float cp = cos(pitch), sp = sin(pitch);
    vec3 forward = vec3(sy * cp, sp, -cy * cp);
    vec3 right = vec3(cy, 0.0, sy);
    vec3 up = cross(right, forward);
    return mat3(right, up, forward);
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
    float s = WaterSpeed;
    for (i=0;i<noctave;i++) {
        res = res + amplitude*noise(f*(p + iTime*s*direction.xz));
        amplitude = amplitude*attenuation;
        f = f*2.0;
        s *= -1.15;
    }
    return res;
}

// TERRAIN FUNCTIONS

float Terrain(vec3 p, int nbOctaves)
{
    float noiseValue = turbulence(p.xz, 2.5, 0.1, 0.46, nbOctaves);

    float a = 0.15;
    float b = -0.19;
    float c = 8.0;
    float d = 0.58;

    if (noiseValue > -a)
    {
        noiseValue = (noiseValue+a)*d*sqrt(abs(noiseValue+a))+b+(pow(noiseValue+a, 2.0)/(c));
    } else {
        noiseValue = (noiseValue+a)*d*sqrt(abs(noiseValue+a))+b-(pow(noiseValue+a, 2.0)/(c-6.));
    }

    return noiseValue - p.y;
}

float Water(vec3 p)
{
    vec3 direction = vec3(1, 0, 0.5);
    float noiseValue = WaterTurbulence(p.xz, 0.04, 0.7, 0.4, 4, direction)/2.;
    direction = rotateY(direction, 1.);
    noiseValue += WaterTurbulence(p.xz, 0.04, 0.7, 0.4, 4, direction)/2.;
    return noiseValue + seaLevel - p.y;
}

vec3 TerrainNormal(in vec3 p, int octaves)
{
    float eps = 0.0001;
    vec3 n;
    float v = Terrain(p, octaves);
    n.x = Terrain( vec3(p.x+eps, p.y, p.z), octaves ) - v;
    n.y = Terrain( vec3(p.x, p.y+eps, p.z), octaves ) - v;
    n.z = Terrain( vec3(p.x, p.y, p.z+eps), octaves ) - v;
    return normalize(n);
}

// Calculate object normal
// p : point
vec3 WaterNormal(in vec3 p )
{
    vec3 direction1 = normalize(vec3(1, 0, 0));
    vec3 direction2 = normalize(vec3(0.3, 0, 1));
    float speed1 = WaterSpeed*0.5;
    float speed2 = -WaterSpeed * 0.6;
    float f1 = 0.20;
    float f2 = 0.70;
    float amplitude1 = 1.0;
    float amplitude2 = 0.6;
    vec2 pos1 = p.xz + direction1.xz * iTime * speed1;
    vec2 pos2 = p.xz + direction2.xz * iTime * speed2;
    vec3 n1 = normalize(sampleWaterNormalMap(pos1*f1));
    vec3 n2 = normalize(sampleWaterNormalMap(pos2*f2));
    return normalize(amplitude1*n1 + amplitude2*n2);
}

// Trace ray using ray marching
float Raytrace(vec3 o, vec3 u, int maxRaySteps, float minDistance, float maxDistance, out bool hitTerrain, out bool hitWater)
{
    hitTerrain = false;
    hitWater = false;

    // Don't start at the origin
    // instead move a little bit forward
    float t=minDistance;

    for(int i=0; i<maxRaySteps; i++)
    {
        vec3 p = o+t*u;
      
        float vTerrain = Terrain(p, 6);
        float vWater = Water(p);
       
        
        // Hit terrain 
        if (vTerrain > 0.0)
        {
            hitTerrain = true;
            break;
        }
        if (vWater > 0.0)
        {
            hitWater = true;
            break;
        }
       
        // Move along ray
        t += max(Epsilon, min(-vTerrain, -vWater)/2.5);  

        // Escape marched far away
        if (t>maxDistance)
        {
            break;
        }
    }
    return t;
}

// Background color
vec3 background(vec3 rd)
{
    return mix(vec3(0.7, 0.8, 1.0), vec3(0.6, 0.9, 1.0), rd.y*1.0+0.25);
    //return mix(vec3(1, 1, 0), vec3(1, 0, 0)*0.9, rd.y*2.0+0.30);
}

// Shading and lighting
// p : point,
// n : normal at point
vec3 ShadeTerrain(vec3 p, vec3 n, vec3 animatedSunPos, bool isShadowed, float sunDistance)
{
    // point light
    const vec3 lightColor = vec3(1.0, 1.0, 1.0);
    
    const vec3 grassColor = vec3(0.05, 0.6, 0.05);
    const vec3 sandColor = vec3(0.85, 0.8, 0.5);
    const vec3 rockColor = vec3(0.42, 0.40, 0.29);
    const vec3 snowColor = vec3(0.9, 0.9, 0.9);

    // ROCHE ET SABLE ET SNOW
    float rockSmoothness = 10.0;
    float grassness = 0.2;
    float snowHeight = 1.9;
    float flatness = clamp(abs(dot(TerrainNormal(p, 3), vec3(0,1,0))) + grassness, 0.0, 1.0);
    vec3 objectColor = mix(sandColor, grassColor, clamp(pow(p.y + 0.8 , 5.0), 0.0, 1.0)); // sand
    objectColor = mix(snowColor, objectColor, pow(clamp((snowHeight - p.y), 0.0, 1.0), 5.0)); // snow
    objectColor = mix(rockColor, objectColor, pow(flatness, rockSmoothness)); // rock

    float dotP = dot(-n, animatedSunPos);

    vec3 c;
    if (dotP < 0.0 || isShadowed) // Ombre
    {
        c = mix(objectColor*0.4, objectColor*0.3, dotP);
    }
    else // Lumiere
    {
        c = lightColor*mix(objectColor*0.5, 0.1+1.2*objectColor, dotP);
    }
    return c;
}

vec3 ShadeWater(vec3 p, vec3 n, vec3 rd, vec3 animatedSunPos, bool castedShadow, float sunDistance)
{
    const vec3 sunColor = vec3(1, 1, 1);

    float terrainHeight = Terrain(p, 2);
    float depth = clamp(p.y - terrainHeight, 0.0, 1.0);
    vec3 objectColor = 0.8*mix(vec3(0.5, 0.7, .9), vec3(0.0), depth*0.25);

    // Specular
    vec3 viewDir = normalize(-rd);
    vec3 reflectDir = reflect(-animatedSunPos, n);
    vec3 specularColor = vec3(1.0, 1.0, 1.0);
    float specular = pow(max(dot(reflectDir, viewDir), 0.0), 32.0);

    // Diffuse
    float dotP = dot(normalize(n), normalize(animatedSunPos));

    castedShadow = castedShadow && (dotP > 0.0);
    bool normalShadow = (dotP <= 0.0);

    vec3 lightColor = sunColor*mix(objectColor*0.75, (0.1 + 1.2*objectColor), dotP);
    vec3 shadowColor = mix(objectColor*0.7, objectColor*0.6, dotP);
    vec3 castedShadowColor = shadowColor; // mix(shadowColor, lightColor, min(sunDistance * 0.15, 1.0));

    vec3 diffuseColor = normalShadow ? shadowColor : castedShadow ? castedShadowColor : lightColor;

    vec3 c = 0.9*diffuseColor + specularColor*specular;

    // Reflection du terrain

    n = mix(n, vec3(0, 1, 0), 0.90);
    vec3 dir = reflect(rd, n);
    bool hitTerrain, hitWater;
    float dist = Raytrace(p, dir, 100, 0.01, 10.0, hitTerrain, hitWater);
    vec3 terrainPos = p+dir*dist;
    if (hitTerrain)
    {
        vec3 terrainColor = ShadeTerrain(terrainPos, TerrainNormal(terrainPos, 1), animatedSunPos, false, 10.0);
        c = mix(c, terrainColor, 0.8);
    }
    else
    {
        //c = mix(c, background(dir), 0.8);
    }



    return c;
}

bool moveCamera(in vec2 fragCoord, out vec3 rd, out vec3 ro, out vec4 dataToStore)
{
    vec4 stored = texture(iChannel1, vec2(0.5) / iResolution.xy);
    vec3 camPos = stored.xyz;
    float yaw = stored.w;
    
    vec4 stored2 = texture(iChannel1, vec2(1.5, 0.5) / iResolution.xy);
    float pitch = stored2.x;
    vec3 prevMouse = stored2.yzw;

    // POSITION PAR DEFAUT DE LA CAMERA
    if (iFrame == 0) {
        camPos = vec3(50.0, 30.0, 0);
        yaw = 0.0;
        pitch = -3.14/2.0;
        prevMouse = vec3(0.0);
    }

    if (iMouse.z > 0.0) {
        vec2 mouseDelta = iMouse.xy - prevMouse.xy;
        if (prevMouse.z > 0.0) {
            yaw += mouseDelta.x * mouseSensitivity / iResolution.x;
            pitch += mouseDelta.y * mouseSensitivity / iResolution.y;
            pitch = clamp(pitch, -1.5, 1.5);
        }
        prevMouse = vec3(iMouse.xy, 1.0);
    } else {
        prevMouse = vec3(iMouse.xy, 0.0);
    }

    mat3 camMat = lookAtMatrix(yaw, pitch);
    vec3 forward = camMat[2];
    vec3 right = camMat[0];

    vec3 moveDir = vec3(0.0);
    
    float dt = iTimeDelta;
    if (isKeyDown(Key_Shift)) dt *= 5.0;

    if (isKeyDown(Key_Z)) moveDir += forward;
    if (isKeyDown(Key_S)) moveDir -= forward;
    if (isKeyDown(Key_D)) moveDir += right;
    if (isKeyDown(Key_Q)) moveDir -= right;
    if (isKeyDown(Key_E)) moveDir.y += 1.0;
    if (isKeyDown(Key_A)) moveDir.y -= 1.0;
    
    if (length(moveDir) > 0.0) {
        camPos += normalize(moveDir) * moveSpeed * dt;
    }

    vec4 storeData1 = vec4(camPos, yaw);
    vec4 storeData2 = vec4(pitch, prevMouse);

    vec2 pixel = (gl_FragCoord.xy / iResolution.xy)*2.0-1.0;
    float aspectRatio = iResolution.x / iResolution.y;
    rd = normalize(vec3(aspectRatio*pixel.x, pixel.y, 2.0));
    rd = camMat * rd;
    ro = camPos;

    if (fragCoord.x < 1.0 && fragCoord.y < 1.0) 
    {
        dataToStore = storeData1;
        return true;
    }
    if (fragCoord.x < 2.0 && fragCoord.x >= 1.0 && fragCoord.y < 1.0) 
    {
        dataToStore = storeData2;
        return true;
    }
    return false;
}

// MAIN

vec3 getColor(vec3 ro, vec3 rd)
{
    vec3 backgroundColor = background(rd);
    vec3 rgb = backgroundColor;

    // Premier rayon pour déterminer les objets touchés

    bool isTerrain, isWater;
    float distance = Raytrace(ro, rd, 250, minRenderDistance, maxRenderDistance, isTerrain, isWater);
    vec3 pos = ro+distance*rd;

    // Deuxième rayon pour savoir si cette position est éclairée par le soleil

    bool isShadowedByTerrain, isShadowedByWater;
    vec3 animatedSunPos = normalize(rotateY(sunPos, iTime*0.06));
    float sunDistance = Raytrace(pos, animatedSunPos, 100, minShadowDistance, maxShadowDistance, isShadowedByTerrain, isShadowedByWater);
    bool isShadowed = isShadowedByTerrain || isShadowedByWater;    
    if (isTerrain || isWater)
    {   
        if (isTerrain)
        {
            vec3 n = TerrainNormal(pos, 8);
            rgb = ShadeTerrain(pos, n, animatedSunPos, isShadowed, sunDistance);
        }
        else if (isWater)
        {
            vec3 n = WaterNormal(pos);
            rgb = ShadeWater(pos, n, rd, animatedSunPos, isShadowed, sunDistance);
        }

        // Ajout de brouillard de distance
        float fogginess = smoothstep(0.95, 1.0, distance / maxRenderDistance);
        rgb = mix(rgb, backgroundColor, fogginess);
    }

    else if (dot(rd, animatedSunPos) > 1.-sunAngle)
    {
        float f = smoothstep(1.-sunAngle, 1.0, dot(rd, animatedSunPos));
        vec3 sunColor = vec3(1.0, 0.9, 0.6);
        rgb += sunColor*f*f;
    }

    return rgb;
}


void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec3 rd, ro;
    vec4 dataToStore;
    
    if (moveCamera(fragCoord, rd, ro, dataToStore)) {
        fragColor = dataToStore;
        return;
    }

    fragColor = vec4(getColor(ro, rd), 1.0);
}

