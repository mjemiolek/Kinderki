#version 430 core
layout (location = 0) in vec3 aPos;

uniform mat4 u_world;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * u_world * vec4(aPos, 1.0);
}