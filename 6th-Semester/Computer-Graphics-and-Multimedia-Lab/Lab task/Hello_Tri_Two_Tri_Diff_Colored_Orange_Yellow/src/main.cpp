#include "glad.h"
#include "glfw3.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex Shader
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Orange Fragment Shader
const char *fragmentShader1Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

// Yellow Fragment Shader
const char *fragmentShader2Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
    "}\n\0";

// Red Fragment Shader
const char *fragmentShader3Source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n\0";


int main()
{
    // Initialize GLFW
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(
        SCR_WIDTH,
        SCR_HEIGHT,
        "LearnOpenGL",
        NULL,
        NULL
    );

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Load OpenGL functions
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // SHADERS
    // Create shaders
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    unsigned int fragmentShaderOrange =
        glCreateShader(GL_FRAGMENT_SHADER);

    unsigned int fragmentShaderYellow =
        glCreateShader(GL_FRAGMENT_SHADER);

    unsigned int fragmentShaderRed =
        glCreateShader(GL_FRAGMENT_SHADER);


    // Create shader programs
    unsigned int shaderProgramOrange = glCreateProgram();
    unsigned int shaderProgramYellow = glCreateProgram();
    unsigned int shaderProgramRed = glCreateProgram();


    // Compile Vertex Shader
    glShaderSource(
        vertexShader,
        1,
        &vertexShaderSource,
        NULL
    );

    glCompileShader(vertexShader);


    // Compile Orange Fragment Shader
    glShaderSource(
        fragmentShaderOrange,
        1,
        &fragmentShader1Source,
        NULL
    );

    glCompileShader(fragmentShaderOrange);


    // Compile Yellow Fragment Shader
    glShaderSource(
        fragmentShaderYellow,
        1,
        &fragmentShader2Source,
        NULL
    );

    glCompileShader(fragmentShaderYellow);


    // Compile Red Fragment Shader
    glShaderSource(
        fragmentShaderRed,
        1,
        &fragmentShader3Source,
        NULL
    );

    glCompileShader(fragmentShaderRed);


    // ORANGE SHADER PROGRAM


    glAttachShader(shaderProgramOrange, vertexShader);
    glAttachShader(shaderProgramOrange, fragmentShaderOrange);

    glLinkProgram(shaderProgramOrange);


    // YELLOW SHADER PROGRAM

    glAttachShader(shaderProgramYellow, vertexShader);
    glAttachShader(shaderProgramYellow, fragmentShaderYellow);

    glLinkProgram(shaderProgramYellow);


    // RED SHADER PROGRAM

    glAttachShader(shaderProgramRed, vertexShader);
    glAttachShader(shaderProgramRed, fragmentShaderRed);

    glLinkProgram(shaderProgramRed);



    // TRIANGLE VERTICES
    

    // Left triangle
    float firstTriangle[] = {
        -0.9f, -0.5f, 0.0f,
        -0.0f, -0.5f, 0.0f,
        -0.45f,  0.5f, 0.0f
    };


    // Middle triangle
    float thirdTriangle[] = {
        -0.45f,  0.5f, 0.0f,
         0.45f,  0.5f, 0.0f,
         0.0f,  -0.5f, 0.0f
    };


    // Right triangle
    float secondTriangle[] = {
         0.0f, -0.5f, 0.0f,
         0.9f, -0.5f, 0.0f,
         0.45f,  0.5f, 0.0f
    };



    // VAO AND VBO


    unsigned int VBOs[3], VAOs[3];

    glGenVertexArrays(3, VAOs);
    glGenBuffers(3, VBOs);



    // LEFT TRIANGLE SETUP


    glBindVertexArray(VAOs[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(firstTriangle),
        firstTriangle,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);


    // MIDDLE TRIANGLE SETUP


    glBindVertexArray(VAOs[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(thirdTriangle),
        thirdTriangle,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);


    // RIGHT TRIANGLE SETUP


    glBindVertexArray(VAOs[2]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(secondTriangle),
        secondTriangle,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);


    // RENDER LOOP

    while (!glfwWindowShouldClose(window))
    {
        // Input
        processInput(window);


        // Clear screen
        glClearColor(
            0.2f,
            0.3f,
            0.3f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);


        // LEFT TRIANGLE - ORANGE

        glUseProgram(shaderProgramOrange);

        glBindVertexArray(VAOs[0]);

        glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );


        // MIDDLE TRIANGLE - RED

        glUseProgram(shaderProgramRed);

        glBindVertexArray(VAOs[1]);

        glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );


        // RIGHT TRIANGLE - YELLOW

        glUseProgram(shaderProgramYellow);

        glBindVertexArray(VAOs[2]);

        glDrawArrays(
            GL_TRIANGLES,
            0,
            3
        );


        // Swap buffers
        glfwSwapBuffers(window);

        // Process events
        glfwPollEvents();
    }


    // CLEANUP
    glDeleteVertexArrays(3, VAOs);
    glDeleteBuffers(3, VBOs);

    glDeleteProgram(shaderProgramOrange);
    glDeleteProgram(shaderProgramYellow);
    glDeleteProgram(shaderProgramRed);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShaderOrange);
    glDeleteShader(fragmentShaderYellow);
    glDeleteShader(fragmentShaderRed);


    // Terminate GLFW
    glfwTerminate();

    return 0;
}


// PROCESS INPUT

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


// FRAMEBUFFER RESIZE CALLBACK

void framebuffer_size_callback(
    GLFWwindow* window,
    int width,
    int height
)
{
    glViewport(
        0,
        0,
        width,
        height
    );
}