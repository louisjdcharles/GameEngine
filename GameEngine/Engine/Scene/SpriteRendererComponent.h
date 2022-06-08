#pragma once

#include "../Assets/ImageAsset.h"

#include <iostream>
#include <entt/entt.hpp>

class SpriteRendererComponent
{
private:
	inline static ImageAsset* defaultImgAsset = nullptr;
	static ImageAsset* GetDefaultImage();

public:
	ImageAsset* ImgAsset;

	SpriteRendererComponent(ImageAsset* imgAsset);
	SpriteRendererComponent();

	void RenderImGui(entt::entity self, entt::registry* registry);

	~SpriteRendererComponent();
};

