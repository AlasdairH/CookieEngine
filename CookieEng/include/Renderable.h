#pragma once

// cstdlib


// external libs

// program
#include "Macro.h"
#include "Component.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "VertexArray.h"
#include "ResourceManager.h"

namespace CookieEng
{
namespace Components
{
	/*! @class Renderable
	*	@brief An Component for providing the data needed to render to the screen
	*
	*	This component contains the data for rendering. This comprises of a Vertex Array Object, an Index Buffer Object and a Material.
	*	The renderer takes this component and uses the getter methods to render to a framebuffer.
	*/
	class Renderable : public ECS::Component
	{
	public:
		/** @brief Sets the mesh data from a ResourceManager name
		*	@param _mesh The string that corresponds to a mesh in the ResourceManager
		*
		*	Takes the given string, looks it up in the resource manager and assigns the mesh pointer member variable.
		*/
		void setMesh(const std::string &_mesh);
		/** @brief Sets the Material data from a ResourceManager name
		*	@param _material The string that corresponds to a Material in the ResourceManager
		*
		*	Takes the given string, looks it up in the resource manager and assigns the Material pointer member variable.
		*/
		void setMaterial(const std::string &_material);

		/** @brief Getter for the Mesh pointer
		*	@return The renderable mesh
		*
		*	Getter for the mesh to be rendered
		*/
		inline std::shared_ptr<Resources::Mesh> getMesh() { return m_mesh; }

		/** @brief Getter for the Material pointer
		*	@return The material to render the mesh with
		*
		*	Getter for the renderables material to go along with the mesh
		*/
		inline std::shared_ptr<Resources::Material> getMaterial() { return m_material; }

	protected:
		std::shared_ptr<Resources::Mesh>			m_mesh;			/**< A shared pointer to the Mesh, typically in the ResourceManager */
		std::shared_ptr<Resources::Material>		m_material;		/**< A shared pointer to the Material, typically in the ResourceManager */
	};
}
}