#include "SpriteRendererComponent.h"

#include <imgui.h>
#include <entt/entt.hpp>

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
	ImgAsset = GetDefaultImage();
}

void SpriteRendererComponent::RenderImGui(entt::entity self, entt::registry& registry);
{
	if (ImGui::CollapsingHeader("Sprite Renderer")) {

		ImGui::BeginGroup();

		ImGui::Text("Sprite Renderer");

		ImGui::Image((void*)ImgAsset->GLTexture->GetId(), { 64, 64 }, { 0, 1 }, { 1, 0 });
		if (ImGui::BeginDragDropTarget())
		{
			if(const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ImageAsset")){
				ImgAsset = *((ImageAsset**)payload->Data);
			}

			ImGui::EndDragDropTarget();
		}
		
		ImGui::Text("Dimensions: %dx%d pixels", ImgAsset->GLTexture->GetWidth(), ImgAsset->GLTexture->GetHeight());

		if (ImGui::Button("Remove")) {
			
		}

		ImGui::EndGroup();
	}
}

SpriteRendererComponent::~SpriteRendererComponent()
{
}
