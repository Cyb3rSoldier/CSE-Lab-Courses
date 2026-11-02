#include "glad.h"
#include "glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float bgRed = 0.2f;
float bgGreen = 0.3f;
float bgBlue = 0.3f;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Lab 2: Interactive GLFW Keyboard Input Controls", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << "=====================================================" << std::endl;
    std::cout << "  Interactive Input Controls Active:" << std::endl;
    std::cout << "  [ESC]       : Exit Program" << std::endl;
    std::cout << "  [R]         : Increase Red Channel" << std::endl;
    std::cout << "  [G]         : Increase Green Channel" << std::endl;
    std::cout << "  [B]         : Increase Blue Channel" << std::endl;
    std::cout << "  [SPACE]     : Reset Background Color" << std::endl;
    std::cout << "=====================================================" << std::endl;

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(bgRed, bgGreen, bgBlue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        bgRed += 0.01f;
        if (bgRed > 1.0f) bgRed = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        bgGreen += 0.01f;
        if (bgGreen > 1.0f) bgGreen = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        bgBlue += 0.01f;
        if (bgBlue > 1.0f) bgBlue = 0.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        bgRed = 0.2f;
        bgGreen = 0.3f;
        bgBlue = 0.3f;
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
