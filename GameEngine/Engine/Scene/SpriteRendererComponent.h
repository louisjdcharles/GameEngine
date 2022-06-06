#pragma once

#include "../Assets/ImageAsset.h"

#include <iostream>

class SpriteRendererComponent
{
private:
	inline static ImageAsset* defaultImgAsset = nullptr;
	static ImageAsset* GetDefaultImage();

public:
	ImageAsset* ImgAsset;

	SpriteRendererComponent(ImageAsset* imgAsset);
	SpriteRendererComponent();

	void RenderImGui();

	~SpriteRendererComponent();
};

