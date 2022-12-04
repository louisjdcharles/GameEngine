// standard library
#include <iostream>
#include <sstream>

// opengl extension loader
#include <glad/glad.h>

// glfw windowing system
#include <GLFW/glfw3.h>

// imgui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

// internal opengl abstractions
#include "Engine/Renderer/Texture.h"
#include "Engine/Renderer/FrameBuffer.h"
#include "Engine/Renderer/IndexBuffer.h"
#include "Engine/Editor/Editor.h"

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

float deltaTime() {
    return 0.5f;
}

int main(void)
{
    Editor e;

    e.Init();
    e.RunLoop();

    return 0;
}
