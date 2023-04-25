#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb_image.h>
#include <string>
#include <iostream>

void loadtextures(std::string texturePath, GLuint* texture);

class Texture
{
private:
    GLuint textureID, textureLocation;
    
public:
    std::string uniform_variable_name;
    Texture();
    Texture(std::string texturePath, std::string uniform_var_name, GLuint sID);
    void bindtexture(std::string uniform_var_name, GLuint shaderID);
    virtual ~Texture();
};

#endif // !TEXTURE_H

