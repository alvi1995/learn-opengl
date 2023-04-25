#version 330 core
out vec4 FragColor;
//in vec4 customcolor;
in vec2 Tex;

uniform sampler2D ftexture;

void main()
{
    FragColor = texture(ftexture, Tex);//* customcolor;
} 