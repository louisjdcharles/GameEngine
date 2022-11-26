#include "Editor.h"

#include <sstream>

#include "../Scene/SpriteRendererComponent.h"
#include "../Scene/TransformComponent.h"
#include "../Scene/BaseEntityComponent.h";

void Editor::RenderSceneView()
{
    ImGui::Begin("Scene");
    ImGui::PopStyleVar(1);

    ImVec2 size = ImGui::GetContentRegionAvail();

    int size_x = (int)size.x;
    int size_y = (int)size.y;

    if ((m_SceneFB == nullptr || size_x != m_SceneFB->GetWidth() || size_y != m_SceneFB->GetHeight()) && size_x > 0 && size_y > 0)
    {
        delete m_SceneFB;

        m_SceneFB = new FrameBuffer(size_x, size_y);
    }

    ImGui::Image((void*)m_SceneFB->GetColorBufferId(), size, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

    ImGui::End();
}

void Editor::RenderHeirarchy()
{
    ImGui::Begin("Heirarchy");

    if (ImGui::Button("Run")) {
        m_Running = true;
        m_CurrentScene.Start();
    }

    if (ImGui::Button("New")) {
        m_CurrentScene.AddObject("New Object");
    }

    entt::registry* scene_registry = m_CurrentScene.GetRegistry();

    auto view = scene_registry->view<BaseEntityComponent>();

    for (auto [entity, base] : view.each()) {

        std::stringstream label;
        label << base.GetName().c_str();
        label << "##";
        label << (int)entity;

        if (ImGui::RadioButton(label.str().c_str(), entity == m_SelectedEntity)) {
            m_SelectedEntity = entity;
        }
    }

    ImGui::End();
}

void Editor::RenderProperties()
{
    entt::registry* scene_registry = m_CurrentScene.GetRegistry();

    ImGui::Begin("Properties");

    if (m_SelectedEntity != entt::null) {
        char nameBuffer[256];
        strcpy_s(nameBuffer, scene_registry->get<BaseEntityComponent>(m_SelectedEntity).GetName().c_str());

        if (ImGui::InputTextWithHint("##EntityNameInput", "name", nameBuffer, 256))
        {
            std::string new_name = nameBuffer;

            scene_registry->get<BaseEntityComponent>(m_SelectedEntity).SetName(new_name);
        }

        if (ImGui::Button("Remove##entity")) {
            scene_registry->destroy(m_SelectedEntity);

            m_SelectedEntity = entt::null;
        }
        else {
            if (ImGui::BeginCombo("##Add Component Dropdown", "Add Component")) {

                if (ImGui::Selectable("Transform") && !scene_registry->any_of<TransformComponent>(m_SelectedEntity)) {
                    scene_registry->emplace<TransformComponent>(m_SelectedEntity);
                }
                else if (ImGui::Selectable("Sprite Renderer") && !scene_registry->any_of<SpriteRendererComponent>(m_SelectedEntity)) {
                    scene_registry->emplace<SpriteRendererComponent>(m_SelectedEntity);
                }

                ImGui::EndCombo();
            }

            if (scene_registry->any_of<TransformComponent>(m_SelectedEntity))
                scene_registry->get<TransformComponent>(m_SelectedEntity).RenderImGui(m_SelectedEntity, scene_registry);

            if (scene_registry->any_of<SpriteRendererComponent>(m_SelectedEntity))
                scene_registry->get<SpriteRendererComponent>(m_SelectedEntity).RenderImGui(m_SelectedEntity, scene_registry);
        }

    }

    ImGui::End();
}

void Editor::Init()
{
	m_Window = new OpenGLWindow();

    m_Window->InitWindow();

	m_AssetManager = new AssetManager();
	m_Renderer = new Renderer();
	m_SelectedEntity = entt::null;

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    io.Fonts->AddFontFromFileTTF("Vendor/imgui/misc/fonts/Roboto-Medium.ttf", 16);

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetGLFWWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void Editor::Render() {

    glfwMakeContextCurrent(m_Window->GetGLFWWindow());
    glfwSwapInterval(1);

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

    RenderSceneView();

    RenderHeirarchy();

    RenderProperties();

    m_AssetManager->RenderImGui();

    ImGui::Render();

    GLFWwindow* backup_current_context = glfwGetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();

    glfwMakeContextCurrent(backup_current_context);

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (m_SceneFB != nullptr) {
        m_CurrentScene.Draw(m_SceneFB, m_Renderer);
    }
}

void Editor::RunLoop() {
    while (!m_Window->ShouldClose())
    {
        if (m_Running)
            m_CurrentScene.Update();

        Render();

        glfwSwapBuffers(m_Window->GetGLFWWindow());

        glfwPollEvents();
    }
}