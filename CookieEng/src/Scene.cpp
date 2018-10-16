#include "Scene.h"

namespace CookieEng
{
namespace Scene
{
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


		m_camera = std::make_shared<Object::Camera>();
		m_camera->setAspectRatio(m_width / (float)m_height);
		m_camera->transform.translate(glm::vec3(0, 0, 8));

		m_entities.emplace_back(ECS::Entity());
		m_entities[0].addComponent<Components::Transform>();
		m_entities[0].addComponent<Components::Renderable>();
		m_entities[0].getComponent<Components::Renderable>()->setMesh("BasicMesh");
		m_entities[0].getComponent<Components::Renderable>()->setMaterial("BasicMaterial");

		Object::Camera::activeCamera = m_camera;
	}

	Scene::~Scene()
	{

	}

	void Scene::onUpdate()
	{
		// update entities
		for (auto entity : m_entities)
		{
			entity.onUpdate();
		}

		Object::Camera::activeCamera->updateCameraUniform();
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