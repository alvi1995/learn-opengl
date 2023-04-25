#include "Shape.h"

static const GLuint coordinate_data_loc_in_buffer = offsetof(vertex, coordinate);
static const GLuint color_data_loc_in_buffer = offsetof(vertex, color);
static const GLuint texture_coordinate_data_in_buffer = offsetof(vertex, textcood);

void load_vertex_buffer_data(GLuint* vbo, vertex* v1, vertex* v2, vertex* v3, vertex* v4 = nullptr)
{
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);

    if (v4 == nullptr)
    {
        glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(vertex), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex), v1);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex), sizeof(vertex), v2);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex) + sizeof(vertex), sizeof(vertex), v3);
    }
    else
    {
        glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(vertex), nullptr, GL_STATIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertex), v1);
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertex), sizeof(vertex), v2);
        glBufferSubData(GL_ARRAY_BUFFER, 2 * sizeof(vertex), sizeof(vertex), v3);
        glBufferSubData(GL_ARRAY_BUFFER, 3 * sizeof(vertex), sizeof(vertex), v4);
    }
}

GLuint determine_offset(GLuint attribute_index)
{
    switch (attribute_index)
    {
    case 0:
        return coordinate_data_loc_in_buffer;
        break;
    case 1:
        return color_data_loc_in_buffer;
        break;
    case 2:
        return texture_coordinate_data_in_buffer;
        break;
    default:
        return coordinate_data_loc_in_buffer;
        break;
    }
}

void enable_vertex_attribute(GLuint attribute_index, GLuint no_of_elements, GLuint *vbo, GLuint *vao)
{
    glBindVertexArray(*vao);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);

    glVertexAttribPointer(attribute_index, no_of_elements, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)(determine_offset(attribute_index)));
    glEnableVertexAttribArray(attribute_index);
}

void buffersetup(vertex* v1, vertex* v2, vertex* v3, GLuint* vbo, GLuint* vao, vertex* v4, GLuint* ebo, GLuint* index, GLuint index_count)
{
    glGenVertexArrays(1, vao);
    glGenBuffers(1, vbo);
    glBindVertexArray(*vao);
    
    if (ebo == nullptr)
    {
        glBindVertexArray(*vao);

        load_vertex_buffer_data(vbo, v1, v2, v3);

        enable_vertex_attribute(0, 4, vbo, vao);
        enable_vertex_attribute(1, 4, vbo, vao);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
    else
    {
        glGenBuffers(1, ebo);
        
        load_vertex_buffer_data(vbo, v1, v2, v3, v4);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(index), index, GL_STATIC_DRAW);

        enable_vertex_attribute(0, 4, vbo, vao);
        enable_vertex_attribute(1, 4, vbo, vao);
        enable_vertex_attribute(2, 2, vbo, vao);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}


Triangle::Triangle(vertex* v1, vertex* v2, vertex* v3)
{
    buffersetup(v1, v2, v3, &vbo, &vao);
}

void Triangle::LinkShader(Shader* s)
{
    trishader = s;
}

void Triangle::rendertri()
{
    glBindVertexArray(vao);
    trishader->use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

Triangle::~Triangle()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    std::cout << "Triangle Destroyed" << std::endl;
}

Quad::Quad(vertex* v1, vertex* v2, vertex* v3, vertex* v4)
    : vbo(0), vao(0), ebo(0), Quadshader(nullptr), is_shader_attached(false), is_texture_attached(false)
{
    GLuint index[6] = {
            0, 1, 2,
            0, 3, 2
    };
    
    buffersetup(v1, v2, v3, &vbo, &vao, v4, &ebo, index);
    std::cout << "Quad Created" << std::endl;
}

Quad::Quad(vertex* v1, vertex* v2, vertex* v3, vertex* v4, GLuint* index, GLuint index_count)
    : vbo(0), vao(0), ebo(0), Quadshader(nullptr), is_shader_attached(false), is_texture_attached(false)
{
    if (index_count != 6)
    {
        std::cout << "index_count has to be 6 for Quad" << std::endl;
    }
    else
    {
        buffersetup(v1, v2, v3, &vbo, &vao, v4, &ebo, index, index_count);
    }
    std::cout << "Quad Created" << std::endl;
}

void Quad::LinkShader(Shader* s)
{
    Quadshader = s;
}

Quad::Quad(vertex* v1, vertex* v2, vertex* v3, vertex* v4, std::string vshader, std::string fshader)
    : vbo(0), vao(0), ebo(0), Quadshader(nullptr), test(vshader.c_str(), fshader.c_str()), is_shader_attached(false), is_texture_attached(false)
{
    GLuint index[6] = {
            0, 1, 2,
            2, 3, 0
    };

    buffersetup(v1, v2, v3, &vbo, &vao, v4, &ebo, index);
    std::cout << "Quad Created" << std::endl;
}

Quad::Quad(vertex* v1, vertex* v2, vertex* v3, vertex* v4, std::string vshader, std::string fshader, std::string tPath, std::string u_v_n)
    : vbo(0), vao(0), ebo(0), Quadshader(nullptr), test(vshader.c_str(), fshader.c_str()), Qt(tPath, u_v_n, test.ID), is_shader_attached(false), is_texture_attached(false)
{
    GLuint index[6] = {
            0, 1, 2,
            2, 3, 0
    };

    buffersetup(v1, v2, v3, &vbo, &vao, v4, &ebo, index);
    std::cout << "Quad Created" << std::endl;
}

void Quad::renderQuad(bool constructorShader)
{
    Qt.bindtexture(Qt.uniform_variable_name, test.ID);
    glBindVertexArray(vao);

    if (constructorShader)
    {
        test.use();
    }
    else
    {
        Quadshader->use();
    }
    
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Quad::~Quad()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);

    std::cout << "Quad Destroyed" << std::endl;
}

cube::cube(Quad* q1, Quad* q2, Quad* q3, Quad* q4, Quad* q5, Quad* q6)
{
    this->q1 = q1;
    this->q2 = q2;
    this->q3 = q3;
    this->q4 = q4;
    this->q5 = q5;
    this->q6 = q6;
    std::cout << "cube Created" << std::endl;
}

void cube::rendercube(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
    q1->test.setMat4("model", model);
    q1->test.setMat4("view", view);
    q1->test.setMat4("projection", projection);
    q1->renderQuad(true);

    q2->test.setMat4("model", model);
    q2->test.setMat4("view", view);
    q2->test.setMat4("projection", projection);
    q2->renderQuad(true);

    q3->test.setMat4("model", model);
    q3->test.setMat4("view", view);
    q3->test.setMat4("projection", projection);
    q3->renderQuad(true);

    q4->test.setMat4("model", model);
    q4->test.setMat4("view", view);
    q4->test.setMat4("projection", projection);
    q4->renderQuad(true);

    q5->test.setMat4("model", model);
    q5->test.setMat4("view", view);
    q5->test.setMat4("projection", projection);
    q5->renderQuad(true);

    q6->test.setMat4("model", model);
    q6->test.setMat4("view", view);
    q6->test.setMat4("projection", projection);
    q6->renderQuad(true);
}

cube::~cube()
{
    std::cout << "cube destroyed" << std::endl;
}