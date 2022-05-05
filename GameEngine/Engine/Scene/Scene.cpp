#include "Scene.h"

#include "TransformComponent.h"
#include "SpriteRendererComponent.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Scene::Scene()
{
	
}

Scene::~Scene()
{
}

void Scene::Start()
{
}

void Scene::Update(float dt)
{
	
}

void Scene::Draw(FrameBuffer* fb, Renderer* renderer)
{
	float ratio = (float)fb->GetWidth() / (float)fb->GetHeight();

	fb->Bind();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 proj = glm::ortho(-ratio, ratio, -1.0f, 1.0f, -100.0f, 100.0f);
	glm::mat4 view = glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.2, 0.2, 1));

	Registry.view<TransformComponent, SpriteRendererComponent>().each([&](TransformComponent& transform, SpriteRendererComponent& spriteRenderer) {
		glm::mat4 mvp = view * proj * transform.GetModelMatrix();

		Texture* tx = spriteRenderer.ImgAsset->GLTexture;

		renderer->DrawSprite(mvp, tx);
	});

	fb->UnBind();
}

GameObject* Scene::AddObject(std::string name)
{
	GameObject* g = new GameObject(&Registry, name);

	return g;
}
