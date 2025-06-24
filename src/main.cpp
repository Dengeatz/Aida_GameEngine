#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Render/ShaderProgram.h";
#include "res/ResourcesManager.h"

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

struct size
{
public:
    int width;
    int height;
};

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    gl::glViewport(0, 0, width, height);
}


int main(int argc, char* argv[]) {


    size windowSize = { 640, 480 };
    glfwInit();
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
    GLFWwindow* window = glfwCreateWindow(windowSize.width, windowSize.height, "OpenGL Testing", NULL, NULL);
    glfwMakeContextCurrent(window);
    glbinding::initialize(glfwGetProcAddress);
    gl::glViewport(0, 0, windowSize.width, windowSize.height);
    gl::glClearColor(0, 0, 0, 1);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    const int verts = 4;

    float polygons[verts * 8] = {
        /*1*/         0.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        /*2*/         0.5f, 0.0f, 0.0f,  1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        /*3*/        -0.5f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        /*4*/         0.0f,  -1.0f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 2,
        1, 2, 3
    };

    {
        auto resourcesManager = &ResourcesManager::Instance(argv[0]);
        auto shaderProgram = resourcesManager->LoadShaders("DefaultShader", "Resources/Shaders/MyVertexShader.vert", "Resources/Shaders/MyFragmentShader.frag");

        if (!shaderProgram->IsCompiled()) {
            std::cerr << "Can't create shader program" << std::endl;
            system("pause");
        }

        auto texture = resourcesManager->LoadTexture("Default texture", "Resources/Textures/images.jpeg");
        auto textureSecond = resourcesManager->LoadTexture("Second texture", "Resources/Textures/awesomeface.png");

        unsigned int VBO, VAO, EBO;
        gl::glGenBuffers(1, &VBO);
        gl::glGenBuffers(1, &EBO);
        gl::glGenVertexArrays(1, &VAO);

        gl::glBindVertexArray(VAO);
        gl::glBindBuffer(gl::GL_ARRAY_BUFFER, VBO);
        gl::glBufferData(gl::GL_ARRAY_BUFFER, sizeof(polygons), polygons, gl::GL_STATIC_DRAW);
        gl::glBindBuffer(gl::GL_ELEMENT_ARRAY_BUFFER, EBO);
        gl::glBufferData(gl::GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, gl::GL_STATIC_DRAW);

#undef GL_FLOAT
        gl::glEnableVertexAttribArray(0);
        gl::glVertexAttribPointer(0, 3, gl::GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
#undef GL_FLOAT
        gl::glEnableVertexAttribArray(1);
        gl::glVertexAttribPointer(1, 3, gl::GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
#undef GL_FLOAT
        gl::glEnableVertexAttribArray(2);
        gl::glVertexAttribPointer(2, 2, gl::GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

        gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
        gl::glBindVertexArray(0);

        shaderProgram->Use();
        shaderProgram->SetTexture("tex", 0);
        shaderProgram->SetTexture("texture2", 1);
        while (!glfwWindowShouldClose(window)) {
            processInput(window);

#undef GL_COLOR_BUFFER_BIT 
            gl::glClear(gl::GL_COLOR_BUFFER_BIT);
            texture->Bind();
            textureSecond->Bind();
            shaderProgram->Use();
            float timeValue = glfwGetTime();
            gl::glBindVertexArray(VAO);
#undef GL_TRIANGLES
#undef GL_UNSIGNED_INT
            gl::glDrawElements(gl::GL_TRIANGLES, 6, gl::GL_UNSIGNED_INT, 0);
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        glfwTerminate();
    }
}