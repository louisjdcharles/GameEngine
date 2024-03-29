#include "Renderer.h"

Renderer::Renderer()
{
	float vertices[4][5]
	{
		{-1, -1, 0, 0.0f, 0.0f},
		{1, -1, 0, 1.0, 0.0f},
		{1, 1, 0, 1.0f, 1.0f},
		{-1, 1, 0, -0.0f, 1.0f},
	};

	unsigned int indices[][3] = {
		{0, 1, 2},
		{2, 3, 0}
	};

	SpriteVB.BufferData(vertices, sizeof(vertices));
	SpriteShader.AddProgram("Engine/Renderer/shader/vert.glsl", "Engine/Renderer/shader/frag.glsl");

	SpriteIB.BufferData(&indices[0][0], 6);

	SpriteVBL.Push<float>(3);
	SpriteVBL.Push<float>(2);

	SpriteVA.AddBuffer(SpriteVB, SpriteVBL);
}

void Renderer::DrawSprite(glm::mat4& transform, Texture* texture, glm::vec4& colour)
{
	SpriteShader.Bind();

	SpriteShader.SetUniform1i("u_Texture", 0);
	SpriteShader.SetUniformMat4f("u_Mvp", transform);
	SpriteShader.SetUniform1i("u_UsesTexture", (int) texture);
	SpriteShader.SetUniform4f("u_Albedo", colour.r, colour.g, colour.b, colour.a);

	if (texture != nullptr)
		texture->Bind();

	SpriteVA.Bind();
	SpriteIB.Bind();

	glDrawElements(GL_TRIANGLES, SpriteIB.GetCount(), GL_UNSIGNED_INT, nullptr);
}
