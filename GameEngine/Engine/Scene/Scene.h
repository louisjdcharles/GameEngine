#pragma once

#include <entt/entt.hpp>

#include <chrono>

#include "../Renderer/FrameBuffer.h"
#include "GameObject.h"
#include "../Renderer/Renderer.h"

class Scene
{
public:
	Scene();
	~Scene();

	void Start();
	void Update();
	void Draw(FrameBuffer* fb, Renderer* renderer);

	GameObject* AddObject(std::string name);

	entt::registry* GetRegistry() { return &m_Registry; }

private:
	entt::registry m_Registry;
	float m_DeltaTime = 0;
	std::chrono::time_point<std::chrono::system_clock> m_Timer;
};

