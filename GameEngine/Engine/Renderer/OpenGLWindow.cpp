#include "OpenGLWindow.h"

#include <iostream>

void OpenGLWindow::ResizeCallback(int newWidth, int newHeight)
{
    m_Dimensions.width = newWidth;
    m_Dimensions.height = newHeight;
    glViewport(0, 0, newWidth, newHeight);
}

int OpenGLWindow::InitWindow()
{
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    m_Window = glfwCreateWindow(m_Dimensions.width, m_Dimensions.height, "Game Engine", NULL, NULL);

    if (!m_Window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMaximizeWindow(m_Window);

    glfwMakeContextCurrent(m_Window);

    glfwSetWindowUserPointer(m_Window, this);

    glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* win, int newWidth, int newHeight) {
        static_cast<OpenGLWindow*>(glfwGetWindowUserPointer(win))->ResizeCallback(newWidth, newHeight);
    });

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << "\n";

    return 0;
}
