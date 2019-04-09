#version 330 core
layout (location = 0) in vec3 aPos;



out vec3 v_color;


void main()
{
    gl_Position = vec4(aPos, 1.0);
    gl_PointSize = 300;
    v_color = vec3(1.0,1.0,1.0);

}
