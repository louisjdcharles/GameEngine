#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "../Renderer/FrameBuffer.h"
#include "../Renderer/Renderer.h"
#include "../Scene/Scene.h"
#include "../Assets/AssetManager.h"
#include "../Renderer/OpenGLWindow.h"

class Editor
{
private:
    OpenGLWindow* m_Window = nullptr;
    FrameBuffer* m_SceneFB = nullptr;
    Renderer* m_Renderer = nullptr;
    Scene m_CurrentScene;
    bool m_Running = false;

    AssetManager* m_AssetManager = nullptr;

    entt::entity m_SelectedEntity = entt::null;

    void RenderSceneView();
    void RenderHeirarchy();
    void RenderProperties();

    void Render();
public:
    Editor() {};
    void Init();
    void RunLoop();
};

