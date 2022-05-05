#include "SpriteRendererComponent.h"

#include <imgui.h>

SpriteRendererComponent::SpriteRendererComponent(ImageAsset* imgAsset)
{
	ImgAsset = imgAsset;
}

void SpriteRendererComponent::RenderImGui()
{
	if (ImGui::CollapsingHeader("Sprite Renderer")) {

		ImGui::BeginGroup();

		ImGui::Text("Sprite Renderer");
		ImGui::Image((void*) ImgAsset->GLTexture->GetId(), {64, 64}, {0, 1}, {1, 0});
		ImGui::Text("Dimensions: %dx%d pixels", ImgAsset->GLTexture->GetWidth(), ImgAsset->GLTexture->GetHeight());

		ImGui::EndGroup();
	}
}
