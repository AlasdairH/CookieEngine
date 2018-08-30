#pragma once

// cstdlib
#include <vector>

// external libs

// program
#include "Vertex.h"

namespace CookieEng
{
namespace Data
{
	// TODO: Consider making this contain a layout of the vertices

	/*! @class Mesh
	*	@brief Data required for a raw Mesh
	*
	*	Contains the data required for a mesh that can be loaded into a VertexBuffer.
	*/
	struct Mesh
	{
		std::vector<Vertex> vertices;		/**< A vector of vertices that stores all the positions, UV data, etc of each vertex */
		std::vector<unsigned int> indices;	/**< The indices for the index buffer that ties all the vertex data together */
	};

}
}