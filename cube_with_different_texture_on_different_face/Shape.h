#ifndef SHAPE_H
#define SHAPE_H

#include <glad/glad.h>
#include "Shader.h"
#include "Texture.h"

struct vertex {
    GLfloat coordinate[4];
    GLfloat color[4];
    GLfloat textcood[2];
};

class Triangle {
private:
    GLuint vao = 0, vbo = 0;
    Shader* trishader = nullptr;

public:
    Triangle(vertex* v1, vertex* v2, vertex* v3);
    void LinkShader(Shader* s);
    void rendertri();
    ~Triangle();
};

class Quad {
private:
    GLuint vao, vbo, ebo;
    Shader* Quadshader;
    bool is_shader_attached;
    bool is_texture_attached;

    bool color_attribute_provided = false;
    bool texture_coordinate_provided = false;
public:
    Shader test;
    Texture Qt;
    Quad(vertex* v1, vertex* v2, vertex* v3, vertex* v4);
    Quad(vertex* v1, vertex* v2, vertex* v3, vertex* v4, GLuint* index, GLuint index_count);
    Quad(vertex* v1, vertex* v2, vertex* v3, vertex* v4, std::string vshader, std::string fshader);
    Quad(vertex* v1, vertex* v2, vertex* v3, vertex* v4, std::string vshader, std::string fshader, std::string tPath, std::string uniform_var_name);
    void LinkShader(Shader* s);
    bool Query_shader_attached();
    bool Query_tesxture_attached();
    void renderQuad(bool constructorShader = true);
    virtual ~Quad();
};

class cube
{
private:
    Quad* q1 = nullptr;
    Quad* q2 = nullptr;
    Quad* q3 = nullptr;
    Quad* q4 = nullptr;
    Quad* q5 = nullptr;
    Quad* q6 = nullptr;
public:
    cube(Quad* q1, Quad* q2, Quad* q3, Quad* q4, Quad* q5, Quad* q6);
    void rendercube(glm::mat4 model, glm::mat4 view = glm::mat4(1.0f), glm::mat4 projection = glm::mat4(1.0f));
    ~cube();
};

//top



void buffersetup(vertex* v1, vertex* v2, vertex* v3, GLuint* vbo, GLuint* vao, vertex* v4 = nullptr, GLuint* ebo = nullptr, GLuint* index = nullptr, GLuint index_count = 6);

#endif // !SHAPE_H

