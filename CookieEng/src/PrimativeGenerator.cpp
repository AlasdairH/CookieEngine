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
			
			std::vector<Vertex> verts;
			for (int i = 0; i < 8; ++i)
			{
				mesh.vertices.push_back(Vertex());
			}
			
			// verts
			mesh.vertices[0].position = _min;													// 0
			mesh.vertices[0].textureCoordinate = glm::vec2(0, 0);								// 0
			mesh.vertices[0].normal = glm::vec3(0);												// 0
			mesh.vertices[1].position = glm::vec3(_min.x + xDif, _min.y       , _min.z);		// 1
			mesh.vertices[1].textureCoordinate = glm::vec2(0, 0);								// 1
			mesh.vertices[1].normal = glm::vec3(0);												// 1
			mesh.vertices[2].position = glm::vec3(_min.x + xDif, _min.y + yDif, _min.z);		// 2
			mesh.vertices[2].textureCoordinate = glm::vec2(0, 0);								// 2
			mesh.vertices[2].normal = glm::vec3(0);												// 2
			mesh.vertices[3].position = glm::vec3(_min.x       , _min.y + yDif, _min.z);		// 3
			mesh.vertices[3].textureCoordinate = glm::vec2(0, 0);								// 3
			mesh.vertices[3].normal = glm::vec3(0);												// 3

			mesh.vertices[4].position = _max;													// 4
			mesh.vertices[4].textureCoordinate = glm::vec2(0, 0);								// 4
			mesh.vertices[4].normal = glm::vec3(0);												// 4
			mesh.vertices[5].position = glm::vec3(_max.x - xDif, _max.y       , _max.z);		// 5
			mesh.vertices[5].textureCoordinate = glm::vec2(0, 0);								// 5
			mesh.vertices[5].normal = glm::vec3(0);												// 5
			mesh.vertices[6].position = glm::vec3(_max.x - xDif, _max.y - yDif, _max.z);		// 6
			mesh.vertices[6].textureCoordinate = glm::vec2(0, 0);								// 6
			mesh.vertices[6].normal = glm::vec3(0);												// 6
			mesh.vertices[7].position = glm::vec3(_max.x       , _max.y - yDif, _max.z);		// 7
			mesh.vertices[7].textureCoordinate = glm::vec2(0, 0);								// 7
			mesh.vertices[7].normal = glm::vec3(0);												// 7


			// 1
			mesh.indices.push_back(0); mesh.indices.push_back(1); mesh.indices.push_back(2);		
			// 2
			mesh.indices.push_back(2); mesh.indices.push_back(3); mesh.indices.push_back(0);		
			// -------------------
			// 3
			mesh.indices.push_back(1); mesh.indices.push_back(7); mesh.indices.push_back(4);
			// 4
			mesh.indices.push_back(4); mesh.indices.push_back(2); mesh.indices.push_back(1);
			// -------------------
			// 5
			mesh.indices.push_back(7); mesh.indices.push_back(6); mesh.indices.push_back(5);
			// 4
			mesh.indices.push_back(5); mesh.indices.push_back(4); mesh.indices.push_back(7);
			// -------------------
			// 6
			mesh.indices.push_back(6); mesh.indices.push_back(0); mesh.indices.push_back(3);
			// 7
			mesh.indices.push_back(3); mesh.indices.push_back(5); mesh.indices.push_back(6);
			// -------------------
			// 8
			mesh.indices.push_back(3); mesh.indices.push_back(2); mesh.indices.push_back(4);
			// 9
			mesh.indices.push_back(4); mesh.indices.push_back(5); mesh.indices.push_back(3);
			// -------------------
			// 10
			mesh.indices.push_back(0); mesh.indices.push_back(1); mesh.indices.push_back(7);
			// 11
			mesh.indices.push_back(7); mesh.indices.push_back(6); mesh.indices.push_back(0);

			return mesh;
		}
	}
}