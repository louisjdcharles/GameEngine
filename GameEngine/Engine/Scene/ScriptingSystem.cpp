#include "ScriptingSystem.h"

#include "TransformComponent.h"

void ScriptingSystem::API_Transform_Translate(uint64_t registry_ptr, uint32_t entity_id, float x, float y, float z)
{
    glm::vec3 v = { x, y, z };

    entt::entity en = static_cast<entt::entity>(entity_id);
    entt::registry* reg = static_cast<entt::registry*>(reinterpret_cast<void*>(registry_ptr));

    TransformComponent::Translate(reg, en, v);
}

/*
struct { float x; float y; float z; } ScriptingSystem::API_Transform_GetPosition(uint64_t registry_ptr, uint32_t entity_id) {
    entt::entity en = static_cast<entt::entity>(entity_id);
    entt::registry* reg = static_cast<entt::registry*>(reinterpret_cast<void*>(registry_ptr));

    glm::vec3 position = TransformComponent::GetPosition(reg, en);

    
}*/

void ScriptingSystem::InitialiseAPI()
{
    m_Domain = mono_jit_init("Application");
    mono_set_dirs(".", ".");

    m_Assembly = mono_domain_assembly_open(m_Domain, "..\\CSTestProject\\bin\\Debug\\CSTestProject.dll");
    m_Image = mono_assembly_get_image(m_Assembly);

    m_BaseEntityClass = mono_class_from_name(m_Image, "CSTestProject.Engine", "EntityScript");

    mono_add_internal_call("CSTestProject.Engine.Transform::__TranslateInternal(ulong,uint,single,single,single)", (const void*) API_Transform_Translate);
    /*mono_add_internal_call("CSTestProject.Engine.Transform::__GetPositionInternal(ulong,uint)", (const void*)API_Transform_GetPosition);*/
}

void ScriptingSystem::SetDeltaTime(float dt)
{
    mono_field_static_set_value(mono_class_vtable(m_Domain, m_BaseEntityClass), mono_class_get_field_from_name(m_BaseEntityClass, "deltaTime"), static_cast<void*>(&dt));
}

ScriptingSystem::~ScriptingSystem()
{
    mono_image_close(m_Image);
    mono_assembly_close(m_Assembly);
    mono_jit_cleanup(m_Domain);
}
