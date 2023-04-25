#version 330 core
layout (location = 0) in vec4 aPos;
//layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTex;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
//out vec4 customcolor;
out vec2 Tex;

void main()
{
    gl_Position = projection*view*model*aPos;
    //customcolor = aColor;
    Tex = aTex;
}