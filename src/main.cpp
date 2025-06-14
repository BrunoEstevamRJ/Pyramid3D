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

#define WINDOW_TITLE "Pyramid"

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

out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 0.5, 0.2, 1.0);  // cor laranja
}
)";

// Vértices da pirâmide: posição (x, y, z), normal (x, y, z), UV (u, v)
float verts[] = {
    // Face de trás
    -0.5f, -0.5f, -0.5f,  0, 0, -1,  0, 0,
     0.5f, -0.5f, -0.5f,  0, 0, -1,  1, 0,
     0.0f,  0.5f,  0.0f,  0, 0, -1,  0.5, 1,

    // Face da frente
    -0.5f, -0.5f,  0.5f,  0, 0, 1,   0, 0,
     0.5f, -0.5f,  0.5f,  0, 0, 1,   1, 0,
     0.0f,  0.5f,  0.0f,  0, 0, 1,   0.5, 1,

    // Face esquerda
    -0.5f, -0.5f, -0.5f, -1, 0, 0,   0, 1,
    -0.5f, -0.5f,  0.5f, -1, 0, 0,   0, 0,
     0.0f,  0.5f,  0.0f, -1, 0, 0,   0.5, 1,

    // Face direita
     0.5f, -0.5f, -0.5f,  1, 0, 0,   0, 1,
     0.5f, -0.5f,  0.5f,  1, 0, 0,   0, 0,
     0.0f,  0.5f,  0.0f,  1, 0, 0,   0.5, 1,
};

GLuint vao, vbo;

void CreateMesh() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    const GLuint stride = sizeof(float) * 8;

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0); // posição
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float))); // normal
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float))); // UV
    glEnableVertexAttribArray(2);
}

GLuint CompileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    // Verifica compilação
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

    // Verifica linking
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
    // Inicializa GLFW e contexto OpenGL 3.3
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Cria janela
    GLFWwindow* window = glfwCreateWindow(800, 600, WINDOW_TITLE, nullptr, nullptr);
    if (!window) {
        std::cerr << "Erro ao criar janela GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    glEnable(GL_DEPTH_TEST); // ativa o teste de profundidade

    CreateMesh();
    GLuint shaderProgram = CreateShaderProgram();

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.2f, 1.0f); // fundo azul escuro
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Matriz model (rotação com o tempo)
        glm::mat4 model = glm::rotate(glm::mat4(1.0f),
                                      (float)glfwGetTime(),
                                      glm::vec3(0.0f, 1.0f, 0.0f));

        glm::mat4 view = glm::translate(glm::mat4(1.0f),
                                        glm::vec3(0.0f, -0.2f, -2.5f));

        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                                800.0f / 600.0f,
                                                0.1f,
                                                100.0f);

        // Envia para o shader
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

        // Renderiza a pirâmide
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 12); // 4 faces (3 vértices por face)

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Finaliza
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
