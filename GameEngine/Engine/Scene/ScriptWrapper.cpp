#include "ScriptWrapper.h"

ScriptWrapper::ScriptWrapper(MonoDomain* domain, MonoClass* klass, GameObject* owner) : m_Owner(owner)
{
	m_Object = mono_object_new(domain, klass);

	mono_runtime_object_init(m_Object);

	m_OnStart = mono_class_get_method_from_name(klass, "OnStart", 0);
	m_OnUpdate = mono_class_get_method_from_name(klass, "OnUpdate", 0);

	uint32_t owner_entity_id = static_cast<uint32_t>(owner->GetId());
	uint64_t owner_registry_ptr =  reinterpret_cast<uint64_t>(static_cast<void*>(owner->GetRegistry()));

	mono_field_set_value(m_Object, mono_class_get_field_from_name(klass, "__internal_id"), &owner_entity_id);

	mono_field_set_value(m_Object, mono_class_get_field_from_name(klass, "__registry_ptr"), &owner_registry_ptr);
}

void ScriptWrapper::CallOnStart()
{
	if (m_OnStart) mono_runtime_invoke(m_OnStart, m_Object, nullptr, nullptr);
}

void ScriptWrapper::CallOnUpdate()
{
	if (m_OnUpdate) mono_runtime_invoke(m_OnUpdate, m_Object, nullptr, nullptr);
}
