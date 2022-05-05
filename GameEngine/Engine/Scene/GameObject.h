#pragma once

#include <entt/entt.hpp>

class GameObject
{
private:
	entt::entity Id;
	entt::registry* Registry;
public:
	GameObject(entt::registry* registry, std::string name);
	~GameObject();

	template<typename T> inline void AddComponent(T component) {
		Registry->emplace<T>(Id, component);
	}

	template<typename T> inline void AddComponent() {
		Registry->emplace<T>(Id);
	}

	template<typename T> inline T& GetComponent() {
		return Registry->get<T>(Id);
	}

	template<typename T> inline void RemoveComponent() {
		Registry->remove<T>(Id);
	}

	entt::entity GetId() const;

	entt::registry* GetRegistry();
};
