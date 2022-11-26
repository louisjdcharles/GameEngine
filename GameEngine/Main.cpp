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

int main(void)
{
    Editor e;

    e.Init();
    /*e.RunLoop();*/


    MonoDomain* domain = mono_jit_init("Application");
    mono_set_dirs(".", ".");
    MonoAssembly* assembly = mono_domain_assembly_open(domain, "..\\CSTestProject\\bin\\Debug\\CSTestProject.dll");
    MonoImage* image = mono_assembly_get_image(assembly);

    MonoClass* testclass = mono_class_from_name(image, "CSTestProject", "ExampleClass");

    MonoMethod* method = mono_class_get_method_from_name(testclass, "Function", 0);

    MonoObject* result;

    result = mono_object_new(domain, testclass);

    mono_runtime_invoke(method, result, nullptr, nullptr);

    return 0;
}
