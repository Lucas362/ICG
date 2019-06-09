#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textcoord;


out vec3 normal_location;
out vec3 frag_loc;
out vec2 text_cd;

uniform mat4 rotation;
uniform mat4 rotation2;


void main()
{
    
    normal_location = normal;

    gl_Position = rotation * rotation2 * vec4(aPos, 1.0);
    frag_loc = gl_Position.xyz;
    text_cd = textcoord;
}
