/*
 * Pyramid.cpp
 *
 *  Criado com o propósito de estudar Programação Gráfica com OpenGL
 *  Autor: BrunoEstevamRJ
 */

#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WINDOW_TITLE "Pyramid"

float lastX = 0.0f, lastY = 0.0f;
float yaw = 0.0f, pitch = 0.0f;
bool firstMouse = true;
bool isDragging = false;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            isDragging = true;
            firstMouse = true;
        } else if (action == GLFW_RELEASE) {
            isDragging = false;
        }
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
    if (!isDragging) return;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        return;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; /*---[ y é invertido: mover pra cima deve aumentar o pitch ]---*/

    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.2f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    /**//*--[ Limita a inclinação vertical ]--*//**/
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
}

const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoord;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    TexCoord = aTexCoord;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture1;
out vec4 FragColor;

void main() {    
    FragColor = texture(texture1, TexCoord);
}
)";

float verts[] = {
    // Front face
    -0.5f, -0.5f, -0.5f,  0, 0, -1,  0, 0,
     0.5f, -0.5f, -0.5f,  0, 0, -1,  1, 0,
     0.0f,  0.5f,  0.0f,  0, 0, -1,  0.5, 1,

    // Back face
    -0.5f, -0.5f,  0.5f,  0, 0, 1,   0, 0,
     0.5f, -0.5f,  0.5f,  0, 0, 1,   1, 0,
     0.0f,  0.5f,  0.0f,  0, 0, 1,   0.5, 1,

    // Left face
    -0.5f, -0.5f, -0.5f, -1, 0, 0,   0, 1,
    -0.5f, -0.5f,  0.5f, -1, 0, 0,   0, 0,
     0.0f,  0.5f,  0.0f, -1, 0, 0,   0.5, 1,

    // Right face
     0.5f, -0.5f, -0.5f,  1, 0, 0,   0, 1,
     0.5f, -0.5f,  0.5f,  1, 0, 0,   0, 0,
     0.0f,  0.5f,  0.0f,  1, 0, 0,   0.5, 1,
};

float baseVerts[] = {
    // Primeiro triângulo
    -0.5f, -0.5f, -0.5f,  0, -1, 0,  0.0f, 0.0f, 
     0.5f, -0.5f, -0.5f,  0, -1, 0,  1.0f, 0.0f, 
     0.5f, -0.5f,  0.5f,  0, -1, 0,  1.0f, 1.0f, 

    // Segundo triângulo
    -0.5f, -0.5f, -0.5f,  0, -1, 0,  0.0f, 0.0f, 
     0.5f, -0.5f,  0.5f,  0, -1, 0,  1.0f, 1.0f, 
    -0.5f, -0.5f,  0.5f,  0, -1, 0,  0.0f, 1.0f  
};

GLuint vao, vbo, baseVao, baseVbo;

void CreateMesh() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(baseVerts), baseVerts, GL_STATIC_DRAW);

    const GLuint stride = sizeof(float) * 8;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float))); 
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    /*--[ Pyramid Base ]--*/
    glGenVertexArrays(1, &baseVao);
    glGenBuffers(1, &baseVbo);

    glBindVertexArray(baseVao);
    glBindBuffer(GL_ARRAY_BUFFER, baseVbo);
    glBufferData(GL_ARRAY_BUFFER,sizeof(baseVerts), baseVerts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0); /*--[ Desvincular VAO ]--*/
}

GLuint CompileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shader, 512, nullptr, log);
        std::cerr << "Erro ao compilar shader:\n" << log << std::endl;
    }

    return shader;
}

GLuint CreateShaderProgram() {
    GLuint vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(program, 512, nullptr, log);
        std::cerr << "Erro ao linkar programa:\n" << log << std::endl;
    }

    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;
}

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, WINDOW_TITLE, nullptr, nullptr);
    if (!window) {
        std::cerr << "Erro ao criar janela GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    /*--[ Register Mouse allbacks ]--*/
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    glEnable(GL_DEPTH_TEST); 

    /*--[ Wrapping e filtering ]--*/
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /*--[ Carregar Imagem ]--*/
    int width, height, nrChannels;
    unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Erro ao carregar imagem wall.jpg\n";
        return -1;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, (nrChannels == 4 ? GL_RGBA : GL_RGB), width, height, 0,
                 (nrChannels == 4 ? GL_RGBA : GL_RGB), GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    GLuint shaderProgram = CreateShaderProgram();
    CreateMesh();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(pitch), glm::vec3(1.0f, 0.0f, 0.0f)); /*--[ Rotação Vertical ]--*/
        model = glm::rotate(model, glm::radians(yaw),   glm::vec3(0.0f, 1.0f, 0.0f)); /*--[ Rotação Horizontal ]--*/

        glm::mat4 view = glm::translate(glm::mat4(1.0f),
                                        glm::vec3(0.0f, -0.2f, -2.5f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                800.0f / 600.0f,
                                                0.1f,
                                                100.0f);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(vao);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

        glDrawArrays(GL_TRIANGLES, 0, 12); 

        glBindVertexArray(baseVao);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}