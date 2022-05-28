#version 430 core
layout (location = 0) in vec3 aPos;        //position
layout (location = 1) in vec3 aNormal;     //normal
layout (location = 2) in vec2 aTexCoords;  //textureCoordinates


out vec4 clipSpace;
out vec2 textureCoords;

uniform mat4 u_world; //transformationMatrix
uniform mat4 projection; //projectionMatrix
uniform mat4 view; //viewMatrix

const float tiling = 6.0;

void main()
{
    vec4 worldPosition = u_world * vec4(aPos, 1.0);
    clipSpace = projection * view * u_world * vec4(aPos, 1.0);
    gl_Position = clipSpace;
    textureCoords = aTexCoords;
}