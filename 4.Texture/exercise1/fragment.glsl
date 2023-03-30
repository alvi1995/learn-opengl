#version 330 core
out vec4 FragColor;
in vec3 customcolor;
in vec2 textureC;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, textureC), texture(texture2, vec2(1.0-textureC.x, textureC.y)), 0.2);
} 