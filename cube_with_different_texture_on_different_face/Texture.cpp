#include "Texture.h"

void loadtextures(std::string texturePath, GLuint* texture)
{
    int width, height, nrChannels;

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}


Texture::Texture() : textureID(0), textureLocation(0) { std::cout << "default constructor" << std::endl; }

Texture::Texture(std::string texturePath, std::string uniform_var_name, GLuint sID)
{
    loadtextures(texturePath.c_str(), &textureID);
    this->uniform_variable_name = uniform_var_name;
    textureLocation = glGetUniformLocation(sID, uniform_var_name.c_str());
    std::cout << "texture created" << std::endl;
}

void Texture::bindtexture(std::string uniform_var_name, GLuint shaderID)
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(textureLocation, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
    std::cout << "texture destoyed" << std::endl;
}

