#pragma once

// cstdlib
#include <vector>

// external libs

// program
#include "Vertex.h"

// TODO: Doxygen
namespace CookieEng
{
namespace Data
{

	struct Mesh
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};

}
}