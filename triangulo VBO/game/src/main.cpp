#include <cmath>
#include <fstream>
#include <iostream>
// Order matters
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

using namespace std;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    cout << "Game On" << endl;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Mac OS only
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Playground", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    int screenWidth = 800;
    int screenHeight = 600;

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


    float rotation[16] ={
        1,0,0,0,
        0,0.5,-0.9,0,
        0,0.9,0.5,0,
        0,0,0,1
    };
    float light[3]= {
        3,0,0
    };
    float vertices[24] = {
        // Front
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,

        // Back
        -0.5f, -0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
    };

    int indices[36] = {
        0,1,2,
        1,2,3,

        1,3,7,
        1,5,7,
        
        2,3,6,
        3,6,7,

        0,4,2,
        4,2,6,

        1,0,4,
        1,4,5,

        5,7,4,
        4,7,6
    };

    float normal[36] = {
        0,0,1,
        0,0,1,

        0,1,0,
        0,1,0,

        1,0,0,
        1,0,0,

        0,-1,0,
        0,-1,0,
        
        -1,0,0,
        -1,0,0,

        0,0,-1,
        0,0,-1
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

    unsigned int transformLoc = glGetUniformLocation(shader.program_id,"rotation");

    glUniformMatrix4fv(transformLoc,1,GL_FALSE, rotation);

    unsigned int lightLoc = glGetUniformLocation(shader.program_id,"light");
    glUniform3fv(lightLoc,1, light);

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

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();

        // Activate VAO
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
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
