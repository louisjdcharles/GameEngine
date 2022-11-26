#pragma once

#include "../Assets/ImageAsset.h"

#include <iostream>
#include <entt/entt.hpp>

#include <imgui.h>

class SpriteRendererComponent
{
private:
	inline static ImageAsset* defaultImgAsset = nullptr;
	static ImageAsset* GetDefaultImage();

public:
	ImageAsset* ImgAsset;
	ImVec4 Albedo = {1.0, 1.0, 1.0, 1.0};
	
	SpriteRendererComponent(ImageAsset* imgAsset);
	SpriteRendererComponent();

	void RenderImGui(entt::entity self, entt::registry* registry);

	~SpriteRendererComponent();
};

