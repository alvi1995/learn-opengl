#version 330 core
out vec4 FragColor;
in vec3 customcolor;
in vec2 textureC;

uniform sampler2D ourtexture;

void main()
{
    FragColor = texture(ourtexture, textureC)*vec4(customcolor, 1.0f);
} 