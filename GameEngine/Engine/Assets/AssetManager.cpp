#include "AssetManager.h"

#include <imgui.h>

AssetManager::AssetManager()
{
	ImageAssets.emplace("test1", new ImageAsset("Engine\\Renderer\\default\\test-sprite.png"));
	ImageAssets.emplace("test2", new ImageAsset("Engine\\Renderer\\default\\uv-test.png"));
}

AssetManager::~AssetManager()
{
}

void AssetManager::RenderImGui()
{
	ImGui::Begin("Asset Manager");

	ImGui::Text("New and improved asset manager!");

	auto dim = ImGui::GetContentRegionAvail();

	int nColumns = dim.x / 100.f;

	ImGui::BeginTable("Image Asset Table", nColumns);

	for (auto [key, img] : ImageAssets) {
		ImGui::TableNextColumn();

		ImGui::Image((void*) img->GLTexture->GetId(), ImVec2{90, 90}, ImVec2{0, 1}, ImVec2{1, 0});
		ImGui::Text(key.c_str());
	}

	ImGui::EndTable();

	ImGui::End();
}

ImageAsset* AssetManager::GetImage(std::string key)
{
	return ImageAssets.at(key);
}
