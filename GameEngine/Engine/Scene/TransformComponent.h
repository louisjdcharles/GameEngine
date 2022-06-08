#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <entt/entt.hpp>

class TransformComponent
{
private:
	glm::vec3 Position;
	float Rotation;
	glm::vec2 Scale;
public:
	TransformComponent();
	TransformComponent(glm::vec3 Position, float rotation, glm::vec2 Scale);
	/*
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(TransformComponent&&) = default;
	TransformComponent& operator = (TransformComponent&&) = default;*/

	glm::vec3 GetPosition() const;
	float GetRotation() const;
	glm::vec2 GetScale() const;

	void Translate(glm::vec3 vector);
	void Rotate(float angle);
	void Enlarge(glm::vec2 amount);

	glm::mat4 GetModelMatrix() const;

	void RenderImGui(entt::entity self, entt::registry* registry);
};

