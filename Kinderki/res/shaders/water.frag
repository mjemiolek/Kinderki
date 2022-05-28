#version 430 core
out vec4 out_Color;  //out_color

in vec4 clipSpace;
in vec2 textureCoords;

uniform sampler2D refractionTexture;
uniform sampler2D reflectionTexture;
uniform sampler2D dudvMap;

uniform float moveFactor;

const float waveStrength = 0.01;

void main(void)
{
    vec2 ndc = (clipSpace.xy/clipSpace.w)/2.0 + 0.5;
    vec2 refractTexCoords = vec2(ndc.x, ndc.y);
    vec2 reflectTexCoords = vec2(ndc.x, -ndc.y);

    vec2 distortion1 = (texture(dudvMap, vec2(textureCoords.x + moveFactor,textureCoords.y)).rg *2.0 - 1.0) * waveStrength;
    vec2 distortion2 = (texture(dudvMap, vec2(-textureCoords.x + moveFactor,textureCoords.y + moveFactor)).rg *2.0 - 1.0) * waveStrength;
    vec2 totalDistortion = distortion1 + distortion2;


    refractTexCoords += totalDistortion;
    refractTexCoords = clamp(refractTexCoords, 0.001, 0.999);

    reflectTexCoords += totalDistortion;
    reflectTexCoords.x = clamp(reflectTexCoords.x, 0.001, 0.999);
    reflectTexCoords.y = clamp(reflectTexCoords.y, -0.999, -0.001);



    vec4 refractColour = texture(refractionTexture, refractTexCoords);
    vec4 reflectColour = texture(reflectionTexture, reflectTexCoords);

    out_Color = mix(refractColour,reflectColour, 0.5);
}