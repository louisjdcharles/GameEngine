#include "FrameBuffer.h"

#include <assert.h>
#include <iostream>

	FrameBuffer::FrameBuffer(int width, int height) : Width(width), Height(height) {
		glGenFramebuffers(1, &Id);

		Bind();

		ColorBufferTexture = new Texture(Width, Height, TextureType::ColorBuffer);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorBufferTexture->GetId(), 0);

		DepthStencilBufferTexture = new Texture(Width, Height, TextureType::DepthStencilBuffer);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, DepthStencilBufferTexture->GetId(), 0);

		glGenRenderbuffers(1, &RenderBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, RenderBuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Width, Height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RenderBuffer);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			assert(false);
		}

		UnBind();
	}

	void FrameBuffer::Bind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, Id);
		glViewport(0, 0, Width, Height);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
	}

	void FrameBuffer::UnBind() const {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	int FrameBuffer::GetWidth() const {
		return Width;
	}

	int FrameBuffer::GetHeight() const {
		return Height;
	}

	GLuint FrameBuffer::GetColorBufferId() const {
		return ColorBufferTexture->GetId();
	}

	FrameBuffer::~FrameBuffer() {
		UnBind();

		delete ColorBufferTexture;
		delete DepthStencilBufferTexture;

		glDeleteRenderbuffers(1, &RenderBuffer);

		glDeleteFramebuffers(1, &Id);
	}