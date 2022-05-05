#pragma once

#include <glad/glad.h>

	class VertexBuffer
	{
	private:
		GLuint Id = 0;
	public:
		VertexBuffer() = default;

		void BufferData(const void* data, GLuint size);

		~VertexBuffer();

		void Bind() const;
		void UnBind() const;
	};

