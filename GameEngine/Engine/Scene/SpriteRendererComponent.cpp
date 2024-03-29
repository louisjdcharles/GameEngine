#include "SpriteRendererComponent.h"

ImageAsset* SpriteRendererComponent::GetDefaultImage()
{
	if (defaultImgAsset == nullptr) {
		defaultImgAsset = new ImageAsset("Engine\\Renderer\\default\\default.png");

		return defaultImgAsset;
	}
	else {
		return defaultImgAsset;
	}
}

SpriteRendererComponent::SpriteRendererComponent(ImageAsset* imgAsset)
{
	ImgAsset = imgAsset;
}

SpriteRendererComponent::SpriteRendererComponent()
{
	ImgAsset = nullptr;
}

void SpriteRendererComponent::RenderImGui(entt::entity self, entt::registry* registry)
{
	if (ImGui::CollapsingHeader("Sprite Renderer")) {

		ImGui::BeginGroup();

		ImGui::Text("Sprite Renderer");

		if (ImgAsset != nullptr) {
			ImGui::Text("Texture:");
			ImGui::Text("Dimensions: %dx%d pixels", ImgAsset->GLTexture->GetWidth(), ImgAsset->GLTexture->GetHeight());
			ImGui::Image((void*)ImgAsset->GLTexture->GetId(), { 64, 64 }, { 0, 1 }, { 1, 0 });
		}
		else
			ImGui::Image((void*) GetDefaultImage()->GLTexture->GetId(), {64, 64}, {0, 1}, {1, 0});

		if (ImGui::BeginDragDropTarget())
		{
			if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ImageAsset")){
				ImgAsset = *((ImageAsset**)payload->Data);
			}

			ImGui::EndDragDropTarget();
		}

		ImGui::ColorEdit4("Colour", (float*)&Albedo, ImGuiColorEditFlags_NoInputs);


		if (ImGui::Button("Remove")) {
			registry->remove<SpriteRendererComponent>(self);
		}

		ImGui::EndGroup();
	}
}

SpriteRendererComponent::~SpriteRendererComponent()
{
}
