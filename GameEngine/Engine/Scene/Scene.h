#pragma once

#include <entt/entt.hpp>

#include "../Renderer/FrameBuffer.h"
#include "GameObject.h"
#include "../Renderer/Renderer.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Start();
	void Update(float dt);
	void Draw(FrameBuffer* fb, Renderer* renderer);

	GameObject* AddObject(std::string name);

	entt::registry* GetRegistry() { return &Registry; }

private:
	entt::registry Registry;
};

