#pragma once

#include "../Assets/ImageAsset.h"

#include <iostream>

class SpriteRendererComponent
{
public:
	ImageAsset* ImgAsset;

	SpriteRendererComponent(ImageAsset* imgAsset);

	void RenderImGui();

	~SpriteRendererComponent()
	{
		std::cout << "sprite renderer destroyed\n";
	}
};

