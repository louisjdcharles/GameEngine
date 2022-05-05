#pragma once

#include <glad/glad.h>

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

	class VertexArray
	{
	private:
		GLuint Id;
	public:
		VertexArray();
		~VertexArray();

		void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

		void Bind() const;
		void UnBind() const;
	};

