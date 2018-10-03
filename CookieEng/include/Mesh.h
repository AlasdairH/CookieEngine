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
		std::vector<Data::Vertex>		vertices;	/**< A vector of vertices that stores all the positions, UV data, etc of each vertex */
		std::vector<unsigned int>		indices;	/**< The indices for the index buffer that ties all the vertex data together */
		
		Graphics::VertexBufferLayout	layout;		/**< The layout of the vertices member */

		/** @brief Loads the Mesh from a file
		*	@param _name The name to assign the mesh
		*	@param _filepath The filepath to load from
		*
		*	Overrides the Resource load to allow loading from a .obj file
		*/
		void load(const std::string &_name, const std::string &_filepath) override;
	};

}
}