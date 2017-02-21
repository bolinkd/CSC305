// Wyvill falloff function
float falloff(float sdist, float iso)
{
    if (sdist <= 0.0) return 1.0;
    if (sdist >= 1.0) return 0.0;
    
    float x = 1.0 - (sdist * sdist) / (iso * iso);
    return max(0.0, x * x * x);
}

float sdSphere(float radius, vec2 center, vec2 p, float iso)
{
    // TODO: Set sdist to the signed distance from the sphere's surface
    float sdist = length(p - center) - radius;
    
    return falloff(sdist, iso);
}

float sdPlane(vec2 normal, vec2 center, vec2 p, float iso)
{
    // TODO: Set sdist to the signed distance from the plane.
    float sdist = dot(normal, p) - dot(normal ,center);
    
    return falloff(sdist, iso);
}

float csgUnion(float d1, float d2)
{
    return max(d1, d2);
}

float csgIntersect(float d1, float d2)
{
    return min(d1, d2);
}

float csgBlend(float d1, float d2)
{
    return clamp(d1 + d2, 0.0, 1.0);
}

float csgDifference(float d1, float d2)
{
    return clamp(d1 - d2, 0.0, 1.0);
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

void mainImage(out vec4 fragColor, in vec2 fragCoord)
{
    vec2 p;
    p = fragCoord.xy / iResolution.xy;
    p.y *= iResolution.y / iResolution.x; // aspect ratio
    
    vec2 mouse = iMouse.xy / iResolution.xy;
    mouse.y *= iResolution.y / iResolution.x; // aspect ratio
    
    float iso = sin(iGlobalTime/2.0);
    
    float sdist = 0.0;
    sdist = sdSphere(0.1, vec2(0.5, 0.3), p, iso);
    sdist = csgUnion(sdist, sdPlane(vec2(1,0),vec2(0.4,0), p, iso));
    // TODO: add a use of csgIntersect and csgDifference to sdist
    sdist = csgBlend(sdist, sdSphere(0.1, vec2(0.4,0.3), p, iso));
    sdist = csgDifference(sdist, sdPlane(vec2(1,1), vec2(0,0.25), p, iso));
    sdist = csgIntersect(sdist, sdSphere(0.25, mouse, p, iso));
    
    
   
    vec3 color = hsv2rgb(vec3(sdist * 0.666, 1.0, 1.0));
    fragColor.xyz = color;
}