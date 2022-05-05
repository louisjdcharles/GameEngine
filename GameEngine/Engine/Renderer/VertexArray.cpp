#include "VertexArray.h"

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &Id);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &Id);
	}

	void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
	{
		Bind();

		vb.Bind();

		unsigned int offset = 0;

		const auto& elements = layout.GetElements();

		for (unsigned int i = 0; i < elements.size(); i++)
		{
			auto const& el = elements[i];

			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, el.Count, el.Type, el.Normalized, layout.GetStride(), (const void*)offset);

			offset += el.Count * GetTypeSize(el.Type);
		}
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(Id);
	}

	void VertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}