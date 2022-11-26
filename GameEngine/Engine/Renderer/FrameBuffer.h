#pragma once

#include <glad/glad.h>
#include "Texture.h"


class FrameBuffer
{
private:
	GLuint Id;
	Texture* ColorBufferTexture = nullptr;
	Texture* DepthStencilBufferTexture = nullptr;
	GLuint RenderBuffer;

	int Width;
	int Height;
public:
	FrameBuffer(int Width, int Height);

	void Bind() const;
	void UnBind() const;

	int GetWidth() const;
	int GetHeight() const;

	GLuint GetColorBufferId() const;

	~FrameBuffer();
};

