#pragma once

#include<unordered_map>

#include "ImageAsset.h"

class AssetManager {
public:
	AssetManager();
	~AssetManager();

	void RenderImGui();

	ImageAsset* GetImage(std::string key);

private:
	std::unordered_map<std::string, ImageAsset*> ImageAssets;
};