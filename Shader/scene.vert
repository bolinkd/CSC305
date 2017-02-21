layout(location = SCENE_POSITION_ATTRIB_LOCATION)
in vec4 Position;

layout(location = SCENE_TEXCOORD_ATTRIB_LOCATION)
in vec2 TexCoord;

layout(location = SCENE_NORMAL_ATTRIB_LOCATION)
in vec3 Normal;

uniform mat4 ModelWorld;
uniform mat4 ModelViewProjection;
uniform mat3 Normal_ModelWorld;

out vec4 fragment_position;
out vec2 fragment_texcoord;
out vec3 fragment_normal;



void main()
{
    // TODO: Set to MVP * P
    gl_Position = ModelViewProjection * Position;

    
    // TODO: Pass vertex attributes to fragment shader
    fragment_position = Position;
    fragment_texcoord = TexCoord;
    fragment_normal = Normal;

}