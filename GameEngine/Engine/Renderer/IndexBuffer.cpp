#include "IndexBuffer.h"

    void IndexBuffer::BufferData(const unsigned int* data, unsigned int count)
    {
        Count = count;
        glGenBuffers(1, &Id);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(unsigned int), data, GL_STATIC_DRAW);
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &Id);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Id);
    }

    void IndexBuffer::UnBind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }