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
#include "Engine/Renderer/Shader.h"
#include "Engine/Renderer/VertexArray.h"
#include "Engine/Renderer/VertexBuffer.h"
#include "Engine/Renderer/VertexBufferLayout.h"

// Scence-Entity-Component
#include "Engine/Scene/GameObject.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/TransformComponent.h"
#include "Engine/Scene/SpriteRendererComponent.h"
#include "Engine/Scene/BaseEntityComponent.h"

// engine asset manager
#include "Engine/Assets/AssetManager.h"

class Application
{
private:
    GLFWwindow* window = nullptr;
    struct { int width; int height; } dimensions = { 1600, 800 };
    FrameBuffer* SceneFB = nullptr;
    Renderer* renderer = nullptr;
    Scene myScene;

    AssetManager* assetManager = nullptr;

    entt::entity selected;

    int InitGLFW();
    int InitOpenGL();
    void InitImGui();
    void RenderImGui();
    void Cleanup();
    void Render();

public:
    Application();
    ~Application();
    int Start();
    void RunLoop();

    void __FBSizeCallback(GLFWwindow* win, int newWidth, int newHeight);
};

Application::Application() {
    
}

Application::~Application() {

}

int Application::Start() {
    if (InitGLFW() != 0) {
        std::cerr << "Error: Failed to initialze glfw!\n";

        return -1;
    }

    if (InitOpenGL() != 0) {
        std::cout << "Error initialising OpenGL\n";

        return -1;
    }

    assetManager = new AssetManager();
    renderer = new Renderer();
    selected = entt::null;

    InitImGui();

    return 0;
}

void Application::Render() {
    glfwSwapInterval(1);

    RenderImGui();

    if (SceneFB != nullptr) {
        myScene.Draw(SceneFB, renderer);
    }
}

void Application::RunLoop() {
    while (!glfwWindowShouldClose(window))
    {
        Render();

        glfwSwapBuffers(window);

        glfwPollEvents();
    }
}

int Application::InitGLFW() {
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(dimensions.width, dimensions.height, "Game Engine", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMaximizeWindow(window);

    glfwMakeContextCurrent(window);
    
    glfwSetWindowUserPointer(window, this);

    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* win, int newWidth, int newHeight) {
        static_cast<Application*>(glfwGetWindowUserPointer(win))->__FBSizeCallback(win, newWidth, newHeight);
    });

    return 0;
}

void Application::__FBSizeCallback(GLFWwindow* win, int newWidth, int newHeight) {
    dimensions.width = newWidth;
    dimensions.height = newHeight;
    glViewport(0, 0, newWidth, newHeight);
}

int Application::InitOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        return -1;
    }

    std::cout << "OpenGL Version " << glGetString(GL_VERSION) << "\n";

    return 0;
}

void Application::InitImGui() {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.Fonts->AddFontFromFileTTF("Vendor/imgui/misc/fonts/Roboto-Medium.ttf", 16);

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void Application::RenderImGui() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    const ImGuiWindowFlags mainWindowFlags =
        ImGuiWindowFlags_MenuBar |
        ImGuiWindowFlags_NoDocking |
        ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoNavFocus;

    ImGui::Begin("Main Window", nullptr, mainWindowFlags);

    ImGui::PopStyleVar(3);

    ImGuiIO& io = ImGui::GetIO();
    ImGuiStyle& style = ImGui::GetStyle();
    float minWinSizeX = style.WindowMinSize.x;
    style.WindowMinSize.x = 370.0f;
    if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
    {
        ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
        ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
    }

    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Open")) {}
            if (ImGui::MenuItem("New")) {}
            if (ImGui::MenuItem("Save")) {}
            if (ImGui::MenuItem("Save As")) {}
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Preferences")) {}
            ImGui::EndMenu();
        }

        ImGui::EndMenuBar();
    }

    ImGui::End();
    
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
    ImGui::Begin("Scene");
    ImGui::PopStyleVar(1);
    
    ImVec2 size = ImGui::GetContentRegionAvail();

    int size_x = (int)size.x;
    int size_y = (int)size.y;

    if ((SceneFB == nullptr || size_x != SceneFB->GetWidth() || size_y != SceneFB->GetHeight()) && size_x > 0 && size_y > 0)
    {
        delete SceneFB;

        SceneFB = new FrameBuffer(size_x, size_y);
    }

    ImGui::Image((void*)SceneFB->GetColorBufferId(), size, ImVec2{0, 1}, ImVec2{1, 0});

    ImGui::End();

    ImGui::Begin("Heirarchy");
    
    if (ImGui::Button("New")) {
        myScene.AddObject("New Object");
    }

    entt::registry* scene_registry = myScene.GetRegistry();

    auto view = scene_registry->view<BaseEntityComponent>();

    for (auto [entity, base] : view.each()) {

        std::stringstream label;
        label << base.GetName().c_str();
        label << "##";
        label << (int) entity;

        if (ImGui::RadioButton(label.str().c_str(), entity == selected)) {
            selected = entity;
        }
    }

    ImGui::End();

    ImGui::Begin("Properties");
    

    if (selected != entt::null) {
        char nameBuffer[256];
        strcpy_s(nameBuffer, scene_registry->get<BaseEntityComponent>(selected).GetName().c_str());

        if (ImGui::InputTextWithHint("##EntityNameInput", "name", nameBuffer, 256))
        {
            std::string new_name = nameBuffer;

            scene_registry->get<BaseEntityComponent>(selected).SetName(new_name);
        }

        if (ImGui::Button("Remove##entity")) {
            scene_registry->destroy(selected);

            selected = entt::null;
            goto skip_render;
        }

        if (ImGui::BeginCombo("##Add Component Dropdown", "Add Component")) {

            if (ImGui::Selectable("Transform") && !scene_registry->any_of<TransformComponent>(selected)) {
                scene_registry->emplace<TransformComponent>(selected);
            }
            else if (ImGui::Selectable("Sprite Renderer") && !scene_registry->any_of<SpriteRendererComponent>(selected)) {
                scene_registry->emplace<SpriteRendererComponent>(selected);
            }

            ImGui::EndCombo();
        }

        if (scene_registry->any_of<TransformComponent>(selected))
            scene_registry->get<TransformComponent>(selected).RenderImGui(selected, scene_registry);

        if (scene_registry->any_of<SpriteRendererComponent>(selected))
            scene_registry->get<SpriteRendererComponent>(selected).RenderImGui(selected, scene_registry);

    }
    skip_render:

    ImGui::End();

    assetManager->RenderImGui();

    ImGui::Render();

    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    glfwMakeContextCurrent(backup_current_context);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Application::Cleanup() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

int main(void)
{
    Application app;

    if (app.Start() == 0)
        app.RunLoop();

    return 0;
}