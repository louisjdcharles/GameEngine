#pragma once

#include <glad/glad.h>

class IndexBuffer
{
private:
	GLuint Id;
	unsigned int Count;
public:
	IndexBuffer() = default;
	void BufferData(const unsigned int* data, unsigned int count);

	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	unsigned int GetCount() const { return Count; }
};

