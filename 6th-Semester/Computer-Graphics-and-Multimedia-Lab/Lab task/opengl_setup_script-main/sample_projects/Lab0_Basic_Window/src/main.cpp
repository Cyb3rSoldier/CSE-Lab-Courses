#include "glad.h"
#include "glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex Shader source code
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

// Fragment Shader source code
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0);\n"
    "}\n\0";

int main()
{
    // Initialize and configure GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab 0: Basic 2D House Graphics", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Initialize GLAD function pointer loader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Build and compile shader program
    // ------------------------------------
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 2D House Geometry Data (Positions X, Y, Z and Colors R, G, B)
    // Modeled after CGM Lab-3.1 (Blue Roof, Yellow House Body, Brown Door, Cyan Windows)
    float vertices[] = {
        // --- 1. ROOF (Blue Triangle) ---
        // Positions            // Colors (RGB)
        -0.9f,  0.2f, 0.0f,    0.1f, 0.3f, 0.8f, // Roof Left
         0.0f,  0.7f, 0.0f,    0.2f, 0.5f, 1.0f, // Roof Top
         0.9f,  0.2f, 0.0f,    0.1f, 0.3f, 0.8f, // Roof Right

        // --- 2. HOUSE BODY (Yellow Quadrilateral / 2 Triangles) ---
        -0.6f, -0.5f, 0.0f,    0.95f, 0.85f, 0.2f,
         0.6f, -0.5f, 0.0f,    0.95f, 0.85f, 0.2f,
         0.6f,  0.2f, 0.0f,    0.95f, 0.85f, 0.2f,

        -0.6f, -0.5f, 0.0f,    0.95f, 0.85f, 0.2f,
         0.6f,  0.2f, 0.0f,    0.95f, 0.85f, 0.2f,
        -0.6f,  0.2f, 0.0f,    0.95f, 0.85f, 0.2f,

        // --- 3. DOOR (Brown Quadrilateral / 2 Triangles) ---
        -0.2f, -0.5f, 0.0f,    0.55f, 0.27f, 0.07f,
         0.2f, -0.5f, 0.0f,    0.55f, 0.27f, 0.07f,
         0.2f,  0.0f, 0.0f,    0.55f, 0.27f, 0.07f,

        -0.2f, -0.5f, 0.0f,    0.55f, 0.27f, 0.07f,
         0.2f,  0.0f, 0.0f,    0.55f, 0.27f, 0.07f,
        -0.2f,  0.0f, 0.0f,    0.55f, 0.27f, 0.07f,

        // --- 4. LEFT WINDOW (Cyan Quad / 2 Triangles) ---
        -0.5f, -0.1f, 0.0f,    0.2f, 0.8f, 0.9f,
        -0.3f, -0.1f, 0.0f,    0.2f, 0.8f, 0.9f,
        -0.3f,  0.1f, 0.0f,    0.2f, 0.8f, 0.9f,

        -0.5f, -0.1f, 0.0f,    0.2f, 0.8f, 0.9f,
        -0.3f,  0.1f, 0.0f,    0.2f, 0.8f, 0.9f,
        -0.5f,  0.1f, 0.0f,    0.2f, 0.8f, 0.9f,

        // --- 5. RIGHT WINDOW (Cyan Quad / 2 Triangles) ---
         0.3f, -0.1f, 0.0f,    0.2f, 0.8f, 0.9f,
         0.5f, -0.1f, 0.0f,    0.2f, 0.8f, 0.9f,
         0.5f,  0.1f, 0.0f,    0.2f, 0.8f, 0.9f,

         0.3f, -0.1f, 0.0f,    0.2f, 0.8f, 0.9f,
         0.5f,  0.1f, 0.0f,    0.2f, 0.8f, 0.9f,
         0.3f,  0.1f, 0.0f,    0.2f, 0.8f, 0.9f
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // Render Loop
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Dark sky background
        glClearColor(0.08f, 0.08f, 0.12f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw House Graphic
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 27); // 3 (Roof) + 6 (Body) + 6 (Door) + 6 (L.Win) + 6 (R.Win) = 27 vertices

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
