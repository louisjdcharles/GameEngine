#include "ScriptComponent.h"

#include <imgui.h>

void ScriptComponent::InitScript(MonoDomain* domain, MonoImage* image, GameObject* owner)
{
	MonoClass* cls = mono_class_from_name(image, m_NameSpace.c_str(), m_Class.c_str());

	m_Wrapper = new ScriptWrapper(domain, cls, owner);
}

void ScriptComponent::RenderImGui(entt::entity self, entt::registry* registry)
{
	ImGui::BeginGroup();

	if (ImGui::CollapsingHeader("Script")) {
		char classNameBuf[256];
		char nameSpaceBuf[256];

		strcpy_s(classNameBuf, m_Class.c_str());
		strcpy_s(nameSpaceBuf, m_NameSpace.c_str());

		if (ImGui::InputText("Class Name", classNameBuf, 256)) {
			m_Class = classNameBuf;
		}

		if (ImGui::InputText("Namespace", nameSpaceBuf, 256)) {
			m_NameSpace = nameSpaceBuf;
		}

		if (ImGui::Button("Remove##Remove Script")) {
			registry->remove<ScriptComponent>(self);
		}
	}

	ImGui::EndGroup();
}
