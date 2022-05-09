#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <stdio.h>
	
TextureFormat getFormats(TextureType type) {
	switch (type) {
	case Image:
		return { GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, 4 };
	case ColorBuffer:
		return { GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, 3 };
	case DepthStencilBuffer:
		return { GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, 4 };
	}
}

Texture::Texture(int width, int height, TextureType type) : Width(width), Height(height),  Type(type) {

	Formats = getFormats(type);

	if (type == Image)
		CpuBuffer = new GLubyte[Width * Height * Formats.BPP];
	else
		CpuBuffer = nullptr;

	glGenTextures(1, &Id);
	glBindTexture(GL_TEXTURE_2D, Id);

	if (type == Image || type == ColorBuffer) {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, Formats.internalFormat, Width, Height, 0, Formats.format, Formats.type, CpuBuffer);
	
	glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint Texture::GetId() const {
	return Id;
}

Texture::~Texture()
{
	glDeleteTextures(1, &Id);
}

Texture::Texture(const std::string& path) {
	stbi_set_flip_vertically_on_load(true);

	CpuBuffer = stbi_load(path.c_str(), &Width, &Height, nullptr, 4);

	Formats = getFormats(Image);

	glGenTextures(1, &Id);
	glBindTexture(GL_TEXTURE_2D, Id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, CpuBuffer);

	stbi_image_free(CpuBuffer);

	UnBind();
}

void Texture::Bind(GLuint slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, Id);
}

void Texture::UnBind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture::GetWidth() const {
	return Width;
}

int Texture::GetHeight() const {
	return Height;
}