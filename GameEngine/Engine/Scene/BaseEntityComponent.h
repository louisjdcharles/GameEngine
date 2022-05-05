#pragma once

#include <string>

#include "GameObject.h"

class BaseEntityComponent {
private:
	std::string Name;
	GameObject* Owner;

public:
	BaseEntityComponent(GameObject* owner, std::string name) : Name(name), Owner(owner) {
		
	}

	std::string GetName() const {
		return Name;
	}

	void SetName(std::string& name) {
		Name = name;
	}

	void Destroy() {
		Owner->GetRegistry()->destroy(Owner->GetId());

		delete Owner;
	}
};