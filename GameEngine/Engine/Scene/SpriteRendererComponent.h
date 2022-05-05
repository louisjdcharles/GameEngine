#pragma once

#include "../Assets/ImageAsset.h"

class SpriteRendererComponent
{
public:
	ImageAsset* ImgAsset;

	SpriteRendererComponent(ImageAsset* imgAsset);

	void RenderImGui();
};

