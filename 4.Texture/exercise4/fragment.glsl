#version 330 core
out vec4 FragColor;
in vec3 customcolor;
in vec2 textureC;

uniform float mixValue;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, textureC), texture(texture2, textureC), mixValue);
} 