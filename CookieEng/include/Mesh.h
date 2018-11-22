#pragma once

// cstdlib
#include <vector>
#include <unordered_map>

// external libs

// program
#include "Resource.h"
#include "Vertex.h"
#include "VertexBufferLayout.h"
#include "ServiceLocator.h"
#include "VertexArray.h"
#include "Times.h"

namespace CookieEng
{
namespace Resources
{
	/*! @class Mesh
	*	@brief Data required for a raw Mesh
	*
	*	Contains the data required for a mesh that can be loaded into a VertexBuffer.
	*/
	struct Mesh : public Resource
	{
		std::vector<Data::Vertex>		vertices;		/**< A vector of vertices that stores all the positions, UV data, etc of each vertex */
		std::vector<unsigned int>		indices;		/**< The indices for the index buffer that ties all the vertex data together */
		
		Graphics::VertexBufferLayout	layout;			/**< The layout of the vertices member */

		/** @brief Loads the Mesh from a file
		*	@param _name The name to assign the mesh
		*	@param _filepath The filepath to load from
		*
		*	Overrides the Resource load to allow loading from a .obj file. This Obj loader is definitely not the fastest or the most efficient but it works! 
		*/
		void load(const std::string &_name, const std::string &_filepath) override;

		/** @brief Getter for the VAO member variable
		*	@return The VAO member variable for use by the renderer
		*
		*	Getter for the VAO member variable (make this friend to Renderer?)
		*/
		inline std::shared_ptr<Graphics::VertexArray> getVAO() { return m_VAO; }
		/** @brief Getter for the IBO member variable
		*	@return The IBO member variable for use by the renderer
		*
		*	Getter for the IBO member variable (make this friend to Renderer?)
		*/
		inline std::shared_ptr<Graphics::VertexBuffer> getIBO() { return m_IBO; }

		/** @brief Getter for the minimum bounding point of the mesh
		*	@return The minimum bounding point of the mesh
		*
		*	Getter for the minimum bounding point of the mesh
		*/
		inline glm::vec3 getMinBoundingPoint() { return m_minBound; }
		/** @brief Getter for the maximum bounding point of the mesh
		*	@return The maximum bounding point of the mesh
		*
		*	Getter for the maximum bounding point of the mesh
		*/
		inline glm::vec3 getMaxBoundingPoint() { return m_maxBound; }

	protected:
		bool										m_loadedToGPU = false;	/**< State flag for if the mash has been loaded to the GPU as a VAO/VBO */
		std::shared_ptr<Graphics::VertexArray>		m_VAO;					/**< The Renderbales VertexArray, set by the loadMesh function */
		std::shared_ptr<Graphics::VertexBuffer>		m_VBO;					/**< The Renderbales VertexBuffer, set by the loadMesh function */
		std::shared_ptr<Graphics::VertexBuffer>		m_IBO;					/**< The Renderbales IndexBuffer, set by the loadMesh function */

		glm::vec3									m_minBound;				/**< The minimum bounding point of the mesh */
		glm::vec3									m_maxBound;				/**< The maximum bounding point of the mesh */
	};

}
}