#include "ShaderCreation.h"

std::string get_file_contents(const char* filename)
{
    std::ifstream in(filename, std::ios::binary); // ios::binary makes sure the data is read or written without translating 
    if (in)                                       // new line characters to and from \r\n on the fly.                                        
    {                                             // In other words, exactly what you give the stream is exactly what's written.
        std::string contents;
        in.seekg(0, std::ios::end);               // goes to the location of last bit 
        contents.resize(in.tellg());              // resize string object to hold the entire text file
        in.seekg(0, std::ios::beg);               // goes to beginning of the file
        in.read(&contents[0], contents.size());   // 
        in.close();
        return(contents);
    }
    throw(errno);
}


Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vshaderSource, fshaderSource;
    int success;
    char infoLog[512];

    vshaderSource = get_file_contents("vertex.glsl");
    const char* vertexShaderSource = vshaderSource.c_str();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    fshaderSource = get_file_contents("fragment.glsl");
    const char* fragmentShaderSource = fshaderSource.c_str();
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);
    glLinkProgram(ID);

    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

Shader::~Shader()
{
    glDeleteProgram(ID);
}