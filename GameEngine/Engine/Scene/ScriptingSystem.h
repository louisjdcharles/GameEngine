#pragma once

#include <entt/entt.hpp>

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <mono/metadata/image.h>


class ScriptingSystem
{
private:
	MonoDomain* m_Domain;
	MonoAssembly* m_Assembly;
	MonoImage* m_Image;

	MonoClass* m_BaseEntityClass;

public:
	ScriptingSystem() {}

	static void API_Transform_Translate(uint64_t registry_ptr, uint32_t entity_id, float x, float y, float z);

	static MonoObject* API_Transform_GetPosition(uint64_t registry_ptr, uint32_t entity_id);

	void InitialiseAPI();

	MonoDomain* GetDomain() { return m_Domain; }
	MonoImage* GetImage() { return m_Image; }

	void SetDeltaTime(float dt);

	~ScriptingSystem();
};

