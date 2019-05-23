#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 normal;



out vec3 v_color;
out vec3 normal_location;

uniform mat4 rotation;
uniform vec3 light;

void main()
{
    gl_Position = rotation * vec4(aPos, 1.0);
    v_color = vec3(1,0,1);
    normal_location = normal;
}
