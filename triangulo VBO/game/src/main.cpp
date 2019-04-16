#include <cmath>
#include <fstream>
#include <iostream>
// Order matters
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shader.hpp"

/* assimp include files. These three are usually needed. */
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

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

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    Assimp::Importer importer;
    std::string path =
        "/home/pablo/repositorioGit/ICG/triangulo VBO/build/game/OBJ.blend";
    const aiScene *scene =
        importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    
    string directory = path.substr(0, path.find_last_of('/'));

    aiMesh *mesh = scene->mMeshes[];
    fprintf(stderr, "ROLA");

    float vertices[mesh->mNumVertices * 3];
    for (unsigned int i = 0; i < mesh->mNumVertices; i = i + 3) {
        vertices[i] = mesh->mVertices[i].x;
        vertices[i + 1] = mesh->mVertices[i].y;
        vertices[i + 2] = mesh->mVertices[i].z;
    }
    int totalFaces = 0;    
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        totalFaces += face.mNumIndices;
    }
    unsigned int indices[mesh->mNumFaces*totalFaces];
    unsigned int k = 0;
    for (unsigned int i = 0; i < mesh->mNumFaces; i++, k++) {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++, k++)
            indices[k] = face.mIndices[j];
    }
    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    Shader shader("game/assets/shaders/vertex.glsl",
                  "game/assets/shaders/fragment.glsl");
    shader.use();

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
        glDrawElements(GL_POINTS, 5, GL_UNSIGNED_INT, 0);
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
