# Pyramid 3D


# 🧱 Pyramid 3D - OpenGL Project

Renderização interativa de uma pirâmide 3D utilizando C++, OpenGL, GLFW, GLAD e GLM.

<div align="center">
  <img src="screenshot.png" alt="Pyramid Preview" width="500"/>
</div>

## 🎯 Objetivo

Este projeto foi desenvolvido com o intuito de estudar programação gráfica moderna (OpenGL 3.3+). Ele mostra como:

- Criar um contexto OpenGL com GLFW.
- Carregar funções com GLAD.
- Utilizar shaders customizados (GLSL).
- Renderizar uma pirâmide 3D com iluminação básica.
- Controlar a visualização da cena com o mouse.

## 📦 Tecnologias Usadas

- **C++17**
- **OpenGL 3.3 Core Profile**
- [GLFW](https://www.glfw.org/)
- [GLAD](https://glad.dav1d.de/)
- [GLM](https://github.com/g-truc/glm)

## 📐 Estrutura

```bash
Pyramid/
├── CMakeLists.txt
├── include/
│   └── (headers, se houver)
├── src/
│   └── main.cpp
├── shaders/
│   ├── vertex.glsl
│   └── fragment.glsl
└── README.md

```

🛠️ Como Compilar
Pré-requisitos

Certifique-se de ter instalado:

    CMake 3.10+

    GCC ou Clang com suporte a C++17

    GLFW, GLAD e GLM

Passos

git clone https://github.com/seuusuario/Pyramid.git
cd Pyramid
mkdir build && cd build
cmake ..
make
./Pyramid

🖱️ Controles

    Arrastar com botão esquerdo do mouse: Gira a pirâmide

    Esc: Fecha a janela

📸 Preview

Imagem de exemplo (adicione uma captura de tela):

![Preview](screenshot.png)

🧠 Créditos

Desenvolvido por Bruno Estevam RJ com foco em aprendizado autodidata de programação gráfica moderna.

📄 Licença

Este projeto está licenciado sob a MIT License.