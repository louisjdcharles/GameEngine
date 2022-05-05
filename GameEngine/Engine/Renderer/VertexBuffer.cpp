#include "VertexBuffer.h"

	void VertexBuffer::BufferData(const void* data, GLuint size) {
		glGenBuffers(1, &Id);
		glBindBuffer(GL_ARRAY_BUFFER, Id);
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

		UnBind();
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &Id);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, Id);
	}

	void VertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}