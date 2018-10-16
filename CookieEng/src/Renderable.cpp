#include "Renderable.h"
namespace CookieEng
{
namespace Components
{
	void Renderable::setMesh(const std::string & _mesh)
	{
		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();
		m_mesh = resourceManager.get<Resources::Mesh>(_mesh);
		loadMesh();
	}

	void Renderable::setMaterial(const std::string & _material)
	{
		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();
		m_material = resourceManager.get<Resources::Material>(_material);
	}

	void Renderable::loadMesh()
	{
		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();

		m_VAO = std::make_shared<Graphics::VertexArray>();
		m_VBO = std::make_shared<Graphics::VertexBuffer>(Graphics::CNG_BUFFER_ARRAY);
		m_IBO = std::make_shared<Graphics::VertexBuffer>(Graphics::CNG_BUFFER_ELEMENT_ARRAY);

		m_VAO->addBuffer(*m_VBO, m_mesh->layout);

		m_VBO->loadData(m_mesh->vertices.data(), 0, m_mesh->layout.getStride() * m_mesh->vertices.size());

		m_IBO->loadData(m_mesh->indices.data(), m_mesh->indices.size(), sizeof(unsigned int) * m_mesh->indices.size());
	}
}
}