#version 330 core
out vec4 FragColor;
in vec3 customcolor;

void main()
{
    FragColor = vec4(customcolor,1.0f);
} 