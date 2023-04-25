#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <string>
#include "Shader.h"
#include "Shape.h"
#include "Texture.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

vertex v0 = { { 0.30f, 0.30f, 0.30f, 1.00f}, {1.0f, 0.0f, 0.0f, 1.00f}, {1.0f, 0.0f} }; //0
vertex v1 = { {-0.30f, 0.30f, 0.30f, 1.00f}, {1.0f, 0.0f, 0.0f, 1.00f}, {0.0f, 0.0f} }; //1
vertex v2 = { {-0.30f, 0.30f,-0.30f, 1.00f}, {1.0f, 0.0f, 0.0f, 1.00f}, {0.0f, 1.0f} }; //2
vertex v3 = { { 0.30f, 0.30f,-0.30f, 1.00f}, {1.0f, 0.0f, 0.0f, 1.00f}, {1.0f, 1.0f} }; //3
//bottom
vertex v4 = { { 0.30f,-0.30f, 0.30f, 1.00f}, {0.0f, 1.0f, 0.0f, 1.00f}, {1.0f, 1.0f} }; //4
vertex v5 = { {-0.30f,-0.30f, 0.30f, 1.00f}, {0.0f, 1.0f, 0.0f, 1.00f}, {0.0f, 1.0f} }; //5
vertex v6 = { {-0.30f,-0.30f,-0.30f, 1.00f}, {0.0f, 1.0f, 0.0f, 1.00f}, {0.0f, 0.0f} }; //6
vertex v7 = { { 0.30f,-0.30f,-0.30f, 1.00f}, {0.0f, 1.0f, 0.0f, 1.00f}, {1.0f, 0.0f} }; //7
//front
vertex v8 = { { 0.30f,-0.30f, 0.30f, 1.00f}, {0.0f, 0.0f, 1.0f, 1.00f}, {1.0f, 0.0f} }; //4
vertex v9 = { {-0.30f,-0.30f, 0.30f, 1.00f}, {0.0f, 0.0f, 1.0f, 1.00f}, {0.0f, 0.0f} }; //5
vertex v10 = { {-0.30f, 0.30f, 0.30f, 1.00f}, {0.0f, 0.0f, 1.0f, 1.00f}, {0.0f, 1.0f} }; //1
vertex v11 = { { 0.30f, 0.30f, 0.30f, 1.00f}, {0.0f, 0.0f, 1.0f, 1.00f}, {1.0f, 1.0f} }; //0
//back
vertex v12 = { { 0.30f,-0.30f,-0.30f, 1.00f}, {1.0f, 1.0f, 0.0f, 1.00f}, {0.0f, 0.0f} }; //7
vertex v13 = { {-0.30f,-0.30f,-0.30f, 1.00f}, {1.0f, 1.0f, 0.0f, 1.00f}, {1.0f, 0.0f} }; //6
vertex v14 = { {-0.30f, 0.30f,-0.30f, 1.00f}, {1.0f, 1.0f, 0.0f, 1.00f}, {1.0f, 1.0f} }; //2
vertex v15 = { { 0.30f, 0.30f,-0.30f, 1.00f}, {1.0f, 1.0f, 0.0f, 1.00f}, {0.0f, 1.0f} }; //3
//right
vertex v16 = { { 0.30f,-0.30f,-0.30f, 1.00f}, {0.0f, 1.0f, 1.0f, 1.00f}, {1.0f, 0.0f} }; //7; 
vertex v17 = { { 0.30f,-0.30f, 0.30f, 1.00f}, {0.0f, 1.0f, 1.0f, 1.00f}, {0.0f, 0.0f} }; //4; 
vertex v18 = { { 0.30f, 0.30f, 0.30f, 1.00f}, {0.0f, 1.0f, 1.0f, 1.00f}, {0.0f, 1.0f} }; //0
vertex v19 = { { 0.30f, 0.30f,-0.30f, 1.00f}, {0.0f, 1.0f, 1.0f, 1.00f}, {1.0f, 1.0f} }; //3
//left
vertex v20 = { {-0.30f,-0.30f,-0.30f, 1.00f}, {1.0f, 0.0f, 1.0f, 1.00f}, {0.0f, 0.0f} }; //6
vertex v21 = { {-0.30f,-0.30f, 0.30f, 1.00f}, {1.0f, 0.0f, 1.0f, 1.00f}, {1.0f, 0.0f} }; //5
vertex v22 = { {-0.30f, 0.30f, 0.30f, 1.00f}, {1.0f, 0.0f, 1.0f, 1.00f}, {1.0f, 1.0f} }; //1
vertex v23 = { {-0.30f, 0.30f,-0.30f, 1.00f}, {1.0f, 0.0f, 1.0f, 1.00f}, {0.0f, 1.0f} }; //2


int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1080, 720, "TriObj", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "ERROR OPENING OPENGL WINDOW" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Quad q1(&v0, &v1, &v2, &v3, "vertex.glsl", "fragment.glsl", "0.jpg", "ftexture");
    Quad q2(&v4, &v5, &v6, &v7, "vertex.glsl", "fragment.glsl", "1.jpg", "ftexture");
    Quad q3(&v8, &v9, &v10, &v11, "vertex.glsl", "fragment.glsl", "2.jpg", "ftexture");
    Quad q4(&v12, &v13, &v14, &v15, "vertex.glsl", "fragment.glsl", "3.jpg", "ftexture");
    Quad q5(&v16, &v17, &v18, &v19, "vertex.glsl", "fragment.glsl", "4.jpg", "ftexture");
    Quad q6(&v20, &v21, &v22, &v23, "vertex.glsl", "fragment.glsl", "5.jpg", "ftexture");

    cube c(&q1, &q2, &q3, &q4, &q5, &q6);

    

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 0.5f, 0.5f));
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);


        c.rendercube(model);
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}