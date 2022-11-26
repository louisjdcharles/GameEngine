#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <glm/glm.hpp>

class Renderer
{
private:
	VertexBuffer SpriteVB;
	IndexBuffer SpriteIB;
	Shader SpriteShader;
	VertexArray SpriteVA;
	VertexBufferLayout SpriteVBL;

public:

	Renderer();

	void DrawSprite(glm::mat4& transform, Texture* texture, glm::vec4& colour);
};

