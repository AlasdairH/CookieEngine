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
		// if the entity being added does not have a Transform component, add one
		if (!_entity.hasComponent<Components::Transform>())
		{
			_entity.addComponent<Components::Transform>();
		}
		m_entities.emplace_back(_entity);
	}

	void Scene::onStart()
	{
		for (auto entity : m_entities)
		{
			entity.onStart();
		}
	}

	void Scene::onUpdate()
	{
		// update entities
		for (auto entity : m_entities)
		{
			entity.onUpdate();
		}

		// update the camera uniform buffer
		if (Object::Camera::activeCamera != nullptr)
		{
			Object::Camera::activeCamera->updateCameraUniform();
		}
	}

	void Scene::draw()
	{
		// bind the framebuffer
		m_frameBuffer->bind();
		for (unsigned int i = 0; i < m_entities.size(); ++i)
		{
			// draw to the framebuffer
			m_renderer.draw(m_entities[i]);
		}
		// unbind the framebuffer
		m_frameBuffer->unBind();
		// draw the framebuffer to the screen
		m_frameBuffer->drawToScreen();
	}
}
}