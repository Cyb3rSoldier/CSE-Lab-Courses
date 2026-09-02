#include "glad.h"
#include "glfw3.h"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
    // Initialize and configure GLFW
    if (!glfwInit())
    {
        std::cerr << "[FAIL] Failed to initialize GLFW." << std::endl;
#ifdef _WIN32
        TerminateProcess(GetCurrentProcess(), 1);
#else
        return -1;
#endif
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Hidden window: Prevents window popups & runs instantly in headless test scripts
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Attempt to create hidden GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL 3.3 Test", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "[FAIL] Failed to create GLFW window with OpenGL 3.3 Core Profile." << std::endl;
#ifdef _WIN32
        TerminateProcess(GetCurrentProcess(), 1);
#else
        glfwTerminate();
        return -1;
#endif
    }

    glfwMakeContextCurrent(window);

    // Initialize GLAD function pointer loader
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "[FAIL] Failed to initialize GLAD." << std::endl;
#ifdef _WIN32
        TerminateProcess(GetCurrentProcess(), 1);
#else
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
#endif
    }

    // Print diagnostic GPU info
    const GLubyte* vendor   = glGetString(GL_VENDOR);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* version  = glGetString(GL_VERSION);
    const GLubyte* glsl     = glGetString(GL_SHADING_LANGUAGE_VERSION);

    std::cout << "[SUCCESS] OpenGL 3.3 Core Profile is supported!" << std::endl;
    if (vendor)   std::cout << "  - GPU Vendor:     " << vendor << std::endl;
    if (renderer) std::cout << "  - Renderer:       " << renderer << std::endl;
    if (version)  std::cout << "  - OpenGL Version: " << version << std::endl;
    if (glsl)     std::cout << "  - GLSL Version:   " << glsl << std::endl;
    std::cout << std::flush;

#ifdef _WIN32
    TerminateProcess(GetCurrentProcess(), 0);
#else
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
#endif
}
