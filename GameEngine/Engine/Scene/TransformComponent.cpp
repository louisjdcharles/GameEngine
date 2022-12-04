#include "TransformComponent.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <limits>

TransformComponent::TransformComponent()
{
	Position = { 0, 0, 0 };
	Rotation = 0;
	Scale = { 1, 1 };
}

TransformComponent::TransformComponent(glm::vec3 position, float rotation, glm::vec2 scale) : Position(position), Rotation(rotation), Scale(scale)
{
	
}

glm::vec3 TransformComponent::GetPosition() const
{
	return Position;
}

float TransformComponent::GetRotation() const
{
	return Rotation;
}

glm::vec2 TransformComponent::GetScale() const
{
	return Scale;
}

void TransformComponent::Translate(glm::vec3 vector)
{
	Position += vector;
}

void TransformComponent::Rotate(float angle)
{
	Rotation += angle;
}

void TransformComponent::Enlarge(glm::vec2 factor)
{
	Scale.x *= factor.x;
	Scale.y *= factor.y;
}

glm::mat4 TransformComponent::GetModelMatrix() const
{
	glm::mat4 model(1);

	model = glm::translate(model, Position);
	model = glm::rotate(model, Rotation, glm::vec3(0, 0, 1));
	model = glm::scale(model, glm::vec3(Scale, 1));

	return model;
}

void TransformComponent::RenderImGui(entt::entity self, entt::registry* registry)
{
	ImGui::BeginGroup();

	if (ImGui::CollapsingHeader("Transform")) {

		ImGui::Columns(2, 0, false);
		ImGui::SetColumnWidth(0, 80);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0,0 });

		ImGui::Text("Position");
		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

		float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;

		ImVec2 buttonSize = { lineHeight + 3.f, lineHeight };

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8, 0.1, 0.1, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.8, 0.1, 0.1, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.9, 0.2, 0.2, 1.0 });
		if (ImGui::Button("X", buttonSize)) {
			Position.x = 0;
		}

		ImGui::PopStyleColor(3);

		ImGui::SameLine();

		ImGui::DragFloat("##X", &Position.x, 0.05);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1, 0.8, 0.1, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1, 0.8, 0.1, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2, 0.9, 0.2, 1.0 });
		if (ImGui::Button("Y", buttonSize)) {
			Position.y = 0;
		}

		ImGui::PopStyleColor(3);

		ImGui::SameLine();


		ImGui::DragFloat("##Y", &Position.y, 0.05);
		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1, 0.1, 0.8, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1, 0.1, 0.8, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2, 0.2, 0.9, 1.0 });
		if (ImGui::Button("Z", buttonSize)) {
			Position.z = 0;
		}
		ImGui::PopStyleColor(3);


		ImGui::SameLine();

		ImGui::DragFloat("##Z", &Position.z, 0.05);

		ImGui::PopItemWidth();

		ImGui::NextColumn();

		ImGui::Text("Scale");

		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.8, 0.1, 0.1, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.8, 0.1, 0.1, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.9, 0.2, 0.2, 1.0 });
		if (ImGui::Button("X##scale", buttonSize)) {
			Scale.x = 1;
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();

		ImGui::DragFloat("##Xscale", &Scale.x, 0.05);

		ImGui::PopItemWidth();
		ImGui::SameLine();

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.1, 0.8, 0.1, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.1, 0.8, 0.1, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.2, 0.9, 0.2, 1.0 });
		if (ImGui::Button("Y##scale", buttonSize)) {
			Scale.y = 1;
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();

		ImGui::DragFloat("##Yscale", &Scale.y, 0.05);

		ImGui::PopItemWidth();
		ImGui::PopItemWidth();

		ImGui::NextColumn();

		ImGui::Text("Rotation");

		ImGui::NextColumn();

		ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());

		ImGui::PushStyleColor(ImGuiCol_Button, { 0.9, 0.9, 0.1, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, { 0.9, 0.9, 0.9, 1.0 });
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 1.0, 1.0, 0.1, 1.0 });
		if (ImGui::Button(u8"°", buttonSize))
		{
			Rotation = 0;
		}
		ImGui::PopStyleColor(3);

		ImGui::SameLine();

		float rotation_degrees = Rotation * (180.f / glm::pi<float>());

		ImGui::DragFloat("##Rotation", &rotation_degrees, 1, 0, 0, "%.1f");

		Rotation = rotation_degrees * (glm::pi<float>() / 180.f);

		ImGui::PopItemWidth();
		ImGui::PopItemWidth();
		ImGui::PopItemWidth();

		ImGui::EndColumns();

		ImGui::PopStyleVar();

		if (ImGui::Button("Remove")) {
			registry->remove<TransformComponent>(self);
		}
	}

	ImGui::EndGroup();
}

void TransformComponent::Translate(entt::registry* reg, entt::entity entity, glm::vec3& vec)
{
	if (reg->any_of<TransformComponent>(entity))
		reg->get<TransformComponent>(entity).Translate(vec);
}

glm::vec3 TransformComponent::GetPosition(entt::registry* reg, entt::entity entity)
{
	if (reg->any_of<TransformComponent>(entity))
		return reg->get<TransformComponent>(entity).GetPosition();
}
