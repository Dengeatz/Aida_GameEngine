#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Render/ShaderProgram.h";

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

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0)\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(1.0, 1.0, 1.0, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec3 FragColor;\n"
"void main()\n"
"{\n"
"    FragColor = vec3(0.0, 1.0, 1.0);\n"
"} \0";

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

    float vertices[] = {
    0.2f, 0.5f, 0.0f,
     -0.2f, 0.2f, 0.0f,
     0.2f, -0.2f, 0.0f,
    };
    const std::string vertexShader = vertexShaderSource;
    const std::string fragmentShader = fragmentShaderSource;

    Render::ShaderProgram shaderProgram(vertexShaderSource, fragmentShaderSource);
    if (!shaderProgram.IsCompiled()) {
        std::cerr << "Can't create shader program" << std::endl;
        system("pause");
    }

    unsigned int VBO, VAO;
    gl::glGenVertexArrays(1, &VAO);
    gl::glGenBuffers(1, &VBO);
    gl::glBindVertexArray(VAO);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, VBO);
    gl::glBufferData(gl::GL_ARRAY_BUFFER, sizeof(vertices), vertices, gl::GL_STATIC_DRAW);
#undef GL_FLOAT
    gl::glVertexAttribPointer(0, 4, gl::GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    gl::glEnableVertexAttribArray(0);
    gl::glBindBuffer(gl::GL_ARRAY_BUFFER, 0);
    gl::glBindVertexArray(0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

#undef GL_COLOR_BUFFER_BIT 
        gl::glClear(gl::GL_COLOR_BUFFER_BIT);

        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        /*int vertexColorLocation = gl::glGetUniformLocation(shaderProgram, "vertexColor");
        int vertexPositionLocation = gl::glGetUniformLocation(shaderProgram, "aPos");
        gl::glUseProgram(shaderProgram);*/
        shaderProgram.Use();
        //gl::glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        //gl::glUniform3f(vertexPositionLocation, greenValue, greenValue, greenValue);
        gl::glBindVertexArray(VAO);
#undef GL_TRIANGLES
        gl::glDrawArrays(gl::GL_TRIANGLES, 0, 3);

        //Another bullshit
        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    glfwTerminate();
}