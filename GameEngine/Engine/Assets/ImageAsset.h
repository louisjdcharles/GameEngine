#pragma once

#include "../Renderer/Texture.h"

class ImageAsset {
public:
	Texture* GLTexture;

	ImageAsset(std::string path) {
		GLTexture = new Texture(path);
	}

	~ImageAsset() {
		delete GLTexture;
	}

};
