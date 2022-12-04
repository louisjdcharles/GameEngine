#pragma once

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>

#include "GameObject.h"
#include <entt/entt.hpp>

class ScriptWrapper
{
private:
	MonoObject* m_Object;
	MonoMethod* m_OnStart;
	MonoMethod* m_OnUpdate;

	GameObject* m_Owner;
public:
	ScriptWrapper(MonoDomain* domain, MonoClass* klass, GameObject* owner);

	void CallOnStart();
	void CallOnUpdate();
};

