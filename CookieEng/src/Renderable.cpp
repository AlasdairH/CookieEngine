#include "Renderable.h"
namespace CookieEng
{
namespace Components
{
	void Renderable::setMesh(const std::string & _mesh)
	{
		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();
		m_mesh = resourceManager.get<Resources::Mesh>(_mesh);
		//loadMesh(); - now handled by mesh
	}

	void Renderable::setMaterial(const std::string & _material)
	{
		
		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();

		m_material = resourceManager.get<Resources::Material>(_material);

	}

	Data::BoundingBox Renderable::getBoundingBox()
	{
		std::shared_ptr<Components::Transform> transform = parent->getComponent<Components::Transform>();
		Data::BoundingBox adjustedAABB;
		adjustedAABB.min = (m_mesh->boundingBox.min + transform->getPositionVec3()) * transform->getScaleVec3();
		adjustedAABB.max = (m_mesh->boundingBox.max + transform->getPositionVec3()) * transform->getScaleVec3();
		return adjustedAABB;
	}
}
}