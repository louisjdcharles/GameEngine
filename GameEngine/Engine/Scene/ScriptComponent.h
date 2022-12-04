#pragma once
#include "ScriptWrapper.h"

class ScriptComponent {
private:
	
public:
	ScriptWrapper* m_Wrapper;

	std::string m_Class = "";
	std::string m_NameSpace = "";

	ScriptComponent() {};

	void InitScript(MonoDomain* domain, MonoImage* image, GameObject* owner);

	void RenderImGui(entt::entity self, entt::registry* registry);
};