#include "Scene.h"

namespace CookieEng
{
namespace Scene
{
	Scene *Scene::activeScene = nullptr;

	Scene::Scene()
	{
		m_frameBuffer = std::make_shared<Graphics::FrameBuffer>(m_width, m_height);
		m_entities.reserve(CNG_MAX_ENTITIES);

		// if there is no current active scene, set it to this one
		if (Scene::activeScene == nullptr)
		{
			activeScene = this;
		}
	}

	Scene::~Scene()
	{

	}

	std::shared_ptr<ECS::Entity> Scene::addEntity(ECS::Entity & _entity)
	{
		// if the entity being added does not have a Transform component, add one
		if (!_entity.hasComponent<Components::Transform>())
		{
			_entity.addComponent<Components::Transform>();
		}
		m_entities.emplace_back(std::make_shared<ECS::Entity>(_entity));
		// reset component parents as the entity will have  moved
		m_entities[m_entities.size() - 1]->resetComponentParents();
		return m_entities[m_entities.size() - 1];
	}

	std::shared_ptr<ECS::Entity> Scene::getEntity(const int _index)
	{
		if ((unsigned int)_index >= m_entities.size())
		{
			LOG_WARNING("Index out of bounds, returning index 0");
			return m_entities[0];
		}

		return m_entities[_index];
	}

	void Scene::removeEntity(std::shared_ptr<ECS::Entity> _entity)
	{
		int index = -1;
		for (unsigned int i = 0; i < m_entities.size(); ++i)
		{
			if (m_entities[i] == _entity)
			{
				index = i;
			}
		}

		if (index != -1)
		{
			LOG_MESSAGE("Removing entity " << index);
			m_entities[index].reset();
			m_entities.erase(m_entities.begin(), m_entities.begin() + index);
		}
		else
		{
			LOG_WARNING("Unable to remove entity, not found in scene");
		}
	}

	void Scene::onStart()
	{
		for (auto entity : m_entities)
		{
			entity->onStart();
		}
	}

	void Scene::onUpdate()
	{
		// update entities
		for (auto entity : m_entities)
		{
			entity->onUpdate();
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
			m_renderer.draw(*m_entities[i]);
		}
		// unbind the framebuffer
		m_frameBuffer->unBind();
		// draw the framebuffer to the screen
		m_frameBuffer->drawToScreen();
	}
}
}