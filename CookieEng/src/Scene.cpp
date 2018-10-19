#include "Scene.h"

namespace CookieEng
{
namespace Scene
{
	Scene *Scene::activeScene = nullptr;

	Scene::Scene()
	{
		m_frameBuffer = std::make_shared<Graphics::FrameBuffer>(m_width, m_height);

		// if there is no current active scene, set it to this one
		if (Scene::activeScene == nullptr)
		{
			activeScene = this;
		}
	}

	Scene::~Scene()
	{

	}

	void Scene::addEntity(ECS::Entity & _entity)
	{
		if (!_entity.hasComponent<Components::Transform>())
		{
			_entity.addComponent<Components::Transform>();
		}
		m_entities.emplace_back(_entity);
	}

	void Scene::onUpdate()
	{
		// update entities
		for (auto entity : m_entities)
		{
			entity.onUpdate();
		}

		if (Object::Camera::activeCamera != nullptr)
		{
			Object::Camera::activeCamera->updateCameraUniform();
		}
	}

	void Scene::draw()
	{
		m_frameBuffer->bind();
		for (unsigned int i = 0; i < m_entities.size(); ++i)
		{
			m_renderer.draw(m_entities[i]);
		}
		m_frameBuffer->unBind();

		m_frameBuffer->drawToScreen();
	}
}
}