#version 330 core

in vec3 v_color;
in vec3 normal_location;

out vec4 FragColor;

uniform vec3 light;

void main()
{
    vec3 calculoDaCarla = normalize(light - normal_location);
    float multCarla = max(dot(calculoDaCarla, normal_location),0);
    FragColor = multCarla * vec4(v_color,1.0);
}