#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class OpenGLWindow
{
private:
	GLFWwindow* m_Window = nullptr;
	struct { int width; int height; } m_Dimensions = { 1600, 800 };

	void ResizeCallback(int newWidth, int newHeight);
public:
	OpenGLWindow(int width, int height) : m_Dimensions({ width, height }) {};
	OpenGLWindow() : m_Dimensions({ 1280, 720 }) {}
	int InitWindow();
	bool ShouldClose() { return glfwWindowShouldClose(m_Window); }

	GLFWwindow* GetGLFWWindow() { return m_Window; }
};

