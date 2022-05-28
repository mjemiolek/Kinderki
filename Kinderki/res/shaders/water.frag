#version 430 core
out vec4 out_Color;  //out_color

in vec4 clipSpace;

uniform sampler2D refractionTexture;
uniform sampler2D reflectionTexture;

void main(void)
{
    vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
    vec2 refractTexCoords = vec2(ndc.x, ndc.y);
    vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

    vec4 refractColour = texture(refractionTexture, refractTexCoords);
    vec4 reflectColour = texture(reflectionTexture, reflectTexCoords);

    out_Color = mix(refractColour,reflectColour, 0.5);
}