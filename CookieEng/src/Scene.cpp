#include "Scene.h"

namespace CookieEng
{
namespace Scene
{
	Scene *Scene::activeScene = nullptr;

	Scene::Scene()
	{
		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();


		m_frameBuffer = std::make_shared<Graphics::FrameBuffer>(m_width, m_height);


		// load meshs
		resourceManager.load<Resources::Mesh>("BasicMesh", "resources/models/Default.obj");

		// load textures
		resourceManager.load<Resources::Texture>("BasicTexture", "resources/textures/Default.png");

		// load shaders
		resourceManager.load<Resources::ShaderProgram>("BasicShader", "resources/shaders/BasicShader.cngShader");

		// load materials
		resourceManager.load<Resources::Material>("BasicMaterial", "resources/materials/Default.cngMaterial");

		// if there is no current active scene, set it to this one
		if (Scene::activeScene == nullptr)
		{
			activeScene = this;
		}
	}

	Scene::~Scene()
	{

	}

	void Scene::addEntity(const ECS::Entity & _entity)
	{
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
		for (unsigned int i = 0; i < m_entities.size(); ++i)
		{
			m_renderer.drawToFrameBuffer(*m_frameBuffer, m_entities[i]);
		}

		m_frameBuffer->drawToScreen();
	}
}
}