#ifndef SHADERCREATION_H
#define SHADERCREATION_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <iostream>

std::string get_file_contents(const char* filename);

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    ~Shader();
};

#endif // !SHADERCREATION_H
