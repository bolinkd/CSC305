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
	vec3 LightPos = vec3(10.0,2.0,0.0);
    // TODO: Replace with Phong shading
    vec3 lightDir = normalize(LightPos - vec3(fragment_position));

    float lambertian = max(dot(lightDir, fragment_normal), 0.0);
    
    float specular = 0.0;

	vec3 viewDir = normalize(CameraPos - fragment_position.xyz);

	vec3 halfDir = normalize(lightDir + viewDir); // Check This
	float specAngle = max(0, dot(halfDir, fragment_normal));
	specular = pow(specAngle, Shininess);

    vec4 diffuseMap = vec4(Diffuse, 1.0);
    if(HasDiffuseMap != 0) {
        diffuseMap = diffuseMap * texture(DiffuseMap, fragment_texcoord).rgba;
    } 

    FragColor = lambertian * diffuseMap
    			+ vec4(Specular, 1.0) * specular;

}