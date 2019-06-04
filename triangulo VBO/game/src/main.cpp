#include <cmath>
#include <fstream>
#include <iostream>
// Order matters
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    cout << "Game On" << endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Mac OS only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Playground", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int screenWidth = 800;
    int screenHeight = 600;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    float rotation[16] = {
        0.5, 0, -0.9, 0,
        0, 1.0, 0, 0,
        0.9, 0, 0.5, 0,
        0, 0, 0, 1};

    float rotation2[16] = {
        1, 0, 0, 0,
        0, 0.5, -0.9, 0,
        0, 0.9, 0.5, 0,
        0, 0, 0, 1};
    float light[3] = {
        1, 0, 0};
    float vertices[108] = {
        // // Front
        // -0.5f,
        // -0.5f,
        // 0.0f,
        // -0.5f,
        // 0.5f,
        // 0.0f,
        // 0.5f,
        // -0.5f,
        // 0.0f,
        // 0.5f,
        // 0.5f,
        // 0.0f,

        // // Back
        // -0.5f,
        // -0.5f,
        // -0.5f,
        // -0.5f,
        // 0.5f,
        // -0.5f,
        // 0.5f,
        // -0.5f,
        // -0.5f,
        // 0.5f,
        // 0.5f,
        // -0.5f,
        -0.5f, -0.5f, 0,
        -0.5, 0.5f, 0,
        0.5f, -0.5f, 0,

        -0.5f, 0.5f, 0,
        0.5f, 0.5f, 0,
        0.5f, -0.5f, 0,

        -0.5f, -0.5f, -1,
        -0.5, 0.5f, -1,
        0.5f, -0.5f, -1,

        -0.5f, 0.5f, -1,
        0.5f, 0.5f, -1,
        0.5f, -0.5f, -1,

        0.5f, -0.5f, 0,
        0.5f, 0.5f, 0,
        0.5f, -0.5f, -1,

        0.5f, 0.5f, 0,
        0.5f, 0.5f, -1,
        0.5f, -0.5f, -1,

        -0.5f, -0.5f, 0,
        -0.5f, 0.5f, 0,
        -0.5f, -0.5f, -1,

        -0.5f, 0.5f, 0,
        -0.5f, 0.5f, -1,
        -0.5f, -0.5f, -1,

        -0.5f, 0.5f, 0,
        -0.5f, 0.5f, -1,
        0.5f, 0.5f, -1,

        -0.5f, 0.5f, 0,
        0.5f, 0.5f, -1,
        0.5f, 0.5f, 0,

        -0.5f, -0.5f, 0,
        -0.5f, -0.5f, -1,
        0.5f, -0.5f, -1,

        -0.5f, -0.5f, 0,
        0.5f, -0.5f, -1,
        0.5f, -0.5f, 0

    };

    int indices[36] = {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,
        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35};

    float normal[108] = {
        0, 0, 1,
        0, 0, 1,
        0, 0, 1,

        0, 0, 1,
        0, 0, 1,
        0, 0, 1,

        0, 0, -1,
        0, 0, -1,
        0, 0, -1,

        0, 0, -1,
        0, 0, -1,
        0, 0, -1,

        1, 0, 0,
        1, 0, 0,
        1, 0, 0,

        1, 0, 0,
        1, 0, 0,
        1, 0, 0,

        -1, 0, 0,
        -1, 0, 0,
        -1, 0, 0,

        -1, 0, 0,
        -1, 0, 0,
        -1, 0, 0,

        0, 1, 0,
        0, 1, 0,
        0, 1, 0,

        0, 1, 0,
        0, 1, 0,
        0, 1, 0,

        0, -1, 0,
        0, -1, 0,
        0, -1, 0,

        0, -1, 0,
        0, -1, 0,
        0, -1, 0

    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int NBO;
    glGenBuffers(1, &NBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    Shader shader("game/assets/shaders/vertex.glsl",
                  "game/assets/shaders/fragment.glsl");
    shader.use();

    unsigned int transformLoc = glGetUniformLocation(shader.program_id, "rotation");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, rotation);
    
    unsigned int transform2Loc = glGetUniformLocation(shader.program_id, "rotation2");
    glUniformMatrix4fv(transform2Loc, 1, GL_FALSE, rotation2);

    // Material
    glUniform3f(glGetUniformLocation(shader.program_id, "material.ambient"), 1.0f, 0.5f, 0.31f); 
    glUniform3f(glGetUniformLocation(shader.program_id, "material.diffuse"), 1.0f, 0.5f, 0.31f); 
    glUniform3f(glGetUniformLocation(shader.program_id, "material.specular"), 0.5f, 0.5f, 0.5f); 
    glUniform1f(glGetUniformLocation(shader.program_id, "material.shininess"), 32.0f); 


    // Light
    glUniform3f(glGetUniformLocation(shader.program_id, "light.position"), 1.2f, 1.0f, 2.0f); 
    glUniform3f(glGetUniformLocation(shader.program_id, "light.ambient"), 0.2f, 0.2f, 0.2f); 
    glUniform3f(glGetUniformLocation(shader.program_id, "light.diffuse"), 0.5f, 0.5f, 0.5f); 
    glUniform3f(glGetUniformLocation(shader.program_id, "light.specular"), 1.0f, 1.0f, 1.0f); 


    // Declare group of Buffers
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    // Activate group of buffers
    glBindVertexArray(VAO);

    // Activate buffer of data. "Use VBO"
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Malloc and Insert Data into buffer, "Insert into vbo..."
    glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);

    // Activate buffer of data. "Use NBO"
    glBindBuffer(GL_ARRAY_BUFFER, NBO);

    // Malloc and Insert Data into buffer, "Insert into vbo..."
    glBufferData(GL_ARRAY_BUFFER, sizeof normal, normal, GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    // Use EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Copy indices to GPU
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices,
                 GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // Deactivate VAO
    glBindVertexArray(0);
    // Or manually deactivate all buffers
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glBindBuffer(GL_ARRAY_BUFFER, 1);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // Activate VAO
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 108, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_POINTS, 0, 3);

        // Deactivate VAO
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}
