#pragma once

#include <glad/glad.h>
#include <string>

	enum TextureType {
		Image,
		ColorBuffer,
		DepthStencilBuffer
	};

	struct TextureFormat {
		GLint internalFormat;
		GLenum format;
		GLenum type;
		int BPP;
	};

	class Texture
	{
	private:
		GLuint Id;
		GLubyte* CpuBuffer;
		int Width, Height;
		
		TextureType Type;
		TextureFormat Formats;
	public:
		Texture(int width, int height, TextureType type);
		Texture(const std::string& path);

		~Texture();

		GLuint GetId() const;
		int GetWidth() const;
		int GetHeight() const;

		void Bind(GLuint slot = 0) const;
		void UnBind() const;

		static Texture LoadFromFile(const std::string& path);
	};

