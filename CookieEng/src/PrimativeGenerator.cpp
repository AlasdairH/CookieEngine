#include "PrimativeGenerator.h"

namespace CookieEng
{
	namespace Data
	{
		Resources::Mesh PrimativeGenerator::generateCube(const glm::vec3 & _min, const glm::vec3 & _max)
		{
			float xDif = _max.x - _min.x;
			float yDif = _max.y - _min.y;
			float zDif = _max.z - _min.z;

			Resources::Mesh mesh;
			mesh.vertices.resize(8);

			//mesh.vertices[1].
			
			// verts
			std::vector<Vertex> verts;
			verts[0].position = _min;													// 0
			verts[0].textureCoordinate = glm::vec2(0, 0);								// 0
			verts[0].normal = glm::vec3(0);												// 0
			verts[1].position = glm::vec3(_min.x + xDif, _min.y       , _min.z);		// 1
			verts[1].textureCoordinate = glm::vec2(0, 0);								// 1
			verts[1].normal = glm::vec3(0);												// 1
			verts[2].position = glm::vec3(_min.x + xDif, _min.y + yDif, _min.z);		// 2
			verts[2].textureCoordinate = glm::vec2(0, 0);								// 2
			verts[2].normal = glm::vec3(0);												// 2
			verts[3].position = glm::vec3(_min.x       , _min.y + yDif, _min.z);		// 3
			verts[3].textureCoordinate = glm::vec2(0, 0);								// 3
			verts[3].normal = glm::vec3(0);												// 3

			verts[4].position = _max;													// 4
			verts[4].textureCoordinate = glm::vec2(0, 0);								// 4
			verts[4].normal = glm::vec3(0);												// 4
			verts[5].position = glm::vec3(_max.x - xDif, _max.y       , _max.z);		// 5
			verts[5].textureCoordinate = glm::vec2(0, 0);								// 5
			verts[5].normal = glm::vec3(0);												// 5
			verts[6].position = glm::vec3(_max.x - xDif, _max.y - yDif, _max.z);		// 6
			verts[6].textureCoordinate = glm::vec2(0, 0);								// 6
			verts[6].normal = glm::vec3(0);												// 6
			verts[7].position = glm::vec3(_max.x       , _max.y - yDif, _max.z);		// 7
			verts[7].textureCoordinate = glm::vec2(0, 0);								// 7
			verts[7].normal = glm::vec3(0);												// 7

			// indices
			std::vector<unsigned int> indicies;
			// 1
			indicies.push_back(0); indicies.push_back(1); indicies.push_back(2);		
			// 2
			indicies.push_back(2); indicies.push_back(3); indicies.push_back(0);		
			// -------------------
			// 3
			indicies.push_back(1); indicies.push_back(7); indicies.push_back(4);
			// 4
			indicies.push_back(4); indicies.push_back(2); indicies.push_back(1);
			// -------------------
			// 5
			indicies.push_back(7); indicies.push_back(6); indicies.push_back(5);
			// 4
			indicies.push_back(5); indicies.push_back(4); indicies.push_back(7);
			// -------------------
			// 6
			indicies.push_back(6); indicies.push_back(0); indicies.push_back(3);
			// 7
			indicies.push_back(3); indicies.push_back(5); indicies.push_back(6);
			// -------------------
			// 8
			indicies.push_back(3); indicies.push_back(2); indicies.push_back(4);
			// 9
			indicies.push_back(4); indicies.push_back(5); indicies.push_back(3);
			// -------------------
			// 10
			indicies.push_back(0); indicies.push_back(1); indicies.push_back(7);
			// 11
			indicies.push_back(7); indicies.push_back(6); indicies.push_back(0);

			mesh.vertices = verts;
			mesh.indices = indicies;

			return mesh;
		}
	}
}