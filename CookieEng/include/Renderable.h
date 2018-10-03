#pragma once

// cstdlib


// external libs

// program
#include "Macro.h"
#include "ECS.h"
#include "Mesh.h"
#include "Material.h"
#include "VertexArray.h"
#include "ResourceManager.h"

// TODO: Doxygen

namespace CookieEng
{
namespace Components
{
	class Renderable : public ECS::Component
	{
	public:
		//void onStart() override;

		void setMesh(const std::string &_mesh);
		void setMaterial(const std::string &_material);
		void loadMesh();

		inline std::shared_ptr<Graphics::VertexArray> getVAO() { return m_VAO; }
		inline std::shared_ptr<Graphics::VertexBuffer> getIBO() { return m_IBO; }
		inline std::shared_ptr<Resources::Material> getMaterial() { return m_material; }

	protected:
		std::shared_ptr<Resources::Mesh> m_mesh;
		std::shared_ptr<Resources::Material> m_material;

		// create a VAO for the vertex data
		std::shared_ptr<Graphics::VertexArray> m_VAO;
		// create a VBO for the vertex data
		std::shared_ptr<Graphics::VertexBuffer> m_VBO;
		// create a IBO for the vertex data
		std::shared_ptr<Graphics::VertexBuffer> m_IBO;
	};
}
}