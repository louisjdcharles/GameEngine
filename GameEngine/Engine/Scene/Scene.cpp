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
	m_Timer = std::chrono::system_clock::now();
}

void Scene::Update()
{
	m_Registry.view<TransformComponent>().each([&](TransformComponent& transform) {
		transform.Translate(m_DeltaTime * glm::vec3(1, 0, 0));
	});

	m_DeltaTime = (float)std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now() - m_Timer).count() / 1'000'000;
	m_Timer = std::chrono::system_clock::now();
}

void Scene::Draw(FrameBuffer* fb, Renderer* renderer)
{
	float ratio = (float)fb->GetWidth() / (float)fb->GetHeight();

	fb->Bind();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 proj = glm::ortho(-ratio, ratio, -1.0f, 1.0f, -100.0f, 100.0f);
	glm::mat4 view = glm::scale(glm::identity<glm::mat4>(), glm::vec3(0.2, 0.2, 1));

	m_Registry.view<TransformComponent, SpriteRendererComponent>().each([&](TransformComponent& transform, SpriteRendererComponent& spriteRenderer) {
		glm::mat4 mvp = view * proj * transform.GetModelMatrix();

		ImageAsset* img = spriteRenderer.ImgAsset;
		glm::vec4 colour = { spriteRenderer.Albedo.x, spriteRenderer.Albedo.y, spriteRenderer.Albedo.z, spriteRenderer.Albedo.w };

		if (img != nullptr) {

			Texture* tx = img->GLTexture;
			renderer->DrawSprite(mvp, tx, colour);
		}
		else {
			renderer->DrawSprite(mvp, nullptr, colour);
		}
	});

	fb->UnBind();
}

GameObject* Scene::AddObject(std::string name)
{
	return new GameObject(&m_Registry, name);
}
