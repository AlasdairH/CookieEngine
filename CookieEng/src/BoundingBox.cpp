#include "BoundingBox.h"

namespace CookieEng
{
namespace Components
{
	BoundingBox BoundingBox::getBoundingBox()
	{
		std::shared_ptr<Transform> transform = parent->getComponent<Transform>();
		BoundingBox adjustedAABB;

		// attempted to do transform...
		glm::vec3 transformedMinPoint = glm::vec4(m_min.x, m_min.y, m_min.z, 0.0f) * transform->getMatrix();
		glm::vec3 transformedMaxPoint = glm::vec4(m_max.x, m_max.y, m_max.z, 0.0f) * transform->getMatrix();

		//adjustedAABB.setMinBoundingPoint(transformedMinPoint);
		//adjustedAABB.setMaxBoundingPoint(transformedMaxPoint);

		adjustedAABB.setMinBoundingPoint((m_min + transform->getPositionVec3()) * transform->getScaleVec3());
		adjustedAABB.setMaxBoundingPoint((m_max + transform->getPositionVec3()) * transform->getScaleVec3());

		return adjustedAABB;
	}

	void BoundingBox::pullFromMesh()
	{
		if (parent->hasComponent<Renderable>())
		{
			std::shared_ptr<Renderable> renderable = parent->getComponent<Renderable>();
			auto mesh = renderable->getMesh();
			if (mesh->isLoaded())
			{
				m_min = mesh->getMinBoundingPoint();
				m_max = mesh->getMaxBoundingPoint();

				m_mesh = Data::PrimativeGenerator::generateCube(m_min, m_max);
				return;
			}
			LOG_WARNING("BoundingBox: Unable to pull size data from mesh, renderable found but has no valid mesh");
			return;
		}
		LOG_WARNING("BoundingBox: Unable to pull size data from mesh, no renderable found");
		return;
	}


	bool BoundingBox::testCollision(const BoundingBox & _other)
	{
		if (m_min.x <= _other.getMaxBoundingPoint().x && m_max.x >= _other.getMinBoundingPoint().x)
		{
			if (m_min.y <= _other.getMaxBoundingPoint().y && m_max.y >= _other.getMinBoundingPoint().y)
			{
				if (m_min.z <= _other.getMaxBoundingPoint().z && m_max.z >= _other.getMinBoundingPoint().z)
				{
					return true;
				}
			}
		}
		return false;
	}

	bool BoundingBox::testCollision(const Data::Ray & _ray)
	{
		double tmin = -INFINITY, tmax = INFINITY;

		for (int i = 0; i < 3; ++i) {
			double t2 = (m_max[i] - _ray.origin[i]) * _ray.inverseDirection[i];
			double t1 = (m_min[i] - _ray.origin[i]) * _ray.inverseDirection[i];

			tmin = CNG_MAX(tmin, CNG_MIN(t1, t2));
			tmax = CNG_MIN(tmax, CNG_MAX(t1, t2));
		}

		return tmax > CNG_MAX(tmin, 0.0);
	}
	}
}