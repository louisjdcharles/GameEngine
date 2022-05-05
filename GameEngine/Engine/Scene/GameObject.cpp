#include "GameObject.h"

#include "BaseEntityComponent.h"

GameObject::GameObject(entt::registry* registry, std::string name = "Unnamed") {
	Registry = registry;

	Id = Registry->create();

	BaseEntityComponent ec(this, name);

	AddComponent<BaseEntityComponent>(ec);
}

GameObject::~GameObject()
{

}

entt::entity GameObject::GetId() const {
	return Id;
}

entt::registry* GameObject::GetRegistry()
{
	return Registry;
}
