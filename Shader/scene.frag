uniform vec3 CameraPos;

uniform vec3 Ambient;
uniform vec3 Diffuse;
uniform vec3 Specular;
uniform float Shininess;

uniform int HasDiffuseMap;
uniform sampler2D DiffuseMap;

in vec4 fragment_position;
in vec2 fragment_texcoord;
in vec3 fragment_normal;

out vec4 FragColor;


void main()
{
	vec3 LightPos = vec3(3.0);
    // TODO: Replace with Phong shading
    vec3 lightDir = normalize(LightPos - vec3(fragment_position));

    float lambertian = max(dot(lightDir, fragment_normal), 0.0);
    
    float specular = 0.0;
    if(lambertian > 0.0){
    	vec4 viewDir = normalize(fragment_position);

    	vec4 halfDir = normalize(vec4(lightDir,1.0) - viewDir);
    	float specAngle = clamp(dot(halfDir, vec4(fragment_normal,1.0)), 0.0, 1.0);
    	specular = pow(specAngle, Shininess);
    }

    vec4 diffuseMap = vec4(Diffuse, 1.0);
    if(HasDiffuseMap != 0) {
        diffuseMap = texture(DiffuseMap, fragment_texcoord).rgba;
    } 

    FragColor = lambertian * diffuseMap
    			+ vec4(Specular, 1.0) * specular;

}