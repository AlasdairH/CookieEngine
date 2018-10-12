#include "Mesh.h"

namespace CookieEng
{
namespace Resources
{
	void Mesh::load(const std::string & _name, const std::string & _filepath)
	{
		vertices.clear();
		indices.clear();
		layout.reset();

		std::string objFile = Services::ServiceLocator::getFileManager().loadTextFile(_filepath);

		unsigned int cursor = 0;

		std::unordered_map<int, glm::vec3> verticesMap;
		std::unordered_map<int, glm::vec3> normals;
		std::unordered_map<int, glm::vec2> textureCoords;

		for (unsigned int i = 0; i < objFile.size(); ++i)
		{
			// find the index of the next end of line char, starting from i
			unsigned int eol = objFile.find("\n", i);
			// get a substring from i, for end of line - i chars
			std::string line = objFile.substr(i, eol - i);



			// vertex line
			if (line.find("v ") != std::string::npos)
			{
				size_t firstSpaceIndex = line.find(" ", 0);
				size_t secondSpaceIndex = line.find(" ", firstSpaceIndex + 1);
				size_t thirdSpaceIndex = line.find(" ", secondSpaceIndex + 1);
				size_t eolIndex = line.find("\n", i);

				std::string xVal = line.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1);
				std::string yVal = line.substr(secondSpaceIndex + 1, thirdSpaceIndex - secondSpaceIndex - 1);
				std::string zVal = line.substr(thirdSpaceIndex + 1, eolIndex - thirdSpaceIndex - 1);

				verticesMap[(int)verticesMap.size() + 1] = glm::vec3(std::stof(xVal), std::stof(yVal), std::stof(zVal));
			}

			// texture coord line
			if (line.find("vt ") != std::string::npos)
			{
				size_t firstSpaceIndex = line.find(" ", 0);
				size_t secondSpaceIndex = line.find(" ", firstSpaceIndex + 1);
				size_t eolIndex = line.find("\n", i);

				std::string xVal = line.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1);
				std::string yVal = line.substr(secondSpaceIndex + 1, eolIndex - secondSpaceIndex - 1);

				textureCoords[(int)textureCoords.size() + 1] = glm::vec2(std::stof(xVal), std::stof(yVal));
			}

			// normal line
			if (line.find("vn ") != std::string::npos)
			{
				unsigned int firstSpaceIndex = line.find(" ", 0);
				unsigned int secondSpaceIndex = line.find(" ", firstSpaceIndex + 1);
				unsigned int thirdSpaceIndex = line.find(" ", secondSpaceIndex + 1);
				unsigned int eolIndex = line.find("\n", i);

				std::string xVal = line.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1);
				std::string yVal = line.substr(secondSpaceIndex + 1, thirdSpaceIndex - secondSpaceIndex - 1);
				std::string zVal = line.substr(thirdSpaceIndex + 1, eolIndex - thirdSpaceIndex - 1);

				normals[(int)normals.size() + 1] = glm::vec3(std::stof(xVal), std::stof(yVal), std::stof(zVal));
			}


			// face line
			if (line.find("f ") != std::string::npos)
			{
				// split the face line
				std::vector<std::string> splitLine = Utilities::UtilsStr::split(line, ' ');
				// remove the "f"
				splitLine.erase(splitLine.begin());

				// create a vector for the extracted indices
				std::vector<int> vIncides;
				std::vector<int> vtIncides;
				std::vector<int> vnIncides;
				// for each split in the face components
				for (unsigned int j = 0; j < splitLine.size(); ++j)
				{
					// split the face components by the slash delimiter
					std::vector<std::string> splitBlock = Utilities::UtilsStr::split(splitLine[j], '/');
					// get the vertex index
					vIncides.push_back(std::stoi(splitBlock[0]));
					// get the vertex texture index
					vtIncides.push_back(std::stoi(splitBlock[1]));
					// get the vertex normal index
					vnIncides.push_back(std::stoi(splitBlock[2]));
				}

				// for the three vertices of a face
				for (unsigned int j = 0; j < 3; ++j)
				{
					Data::Vertex vert;
					// grab the split data for the current vertex and store it together 
					vert.position = glm::vec3(verticesMap[vIncides[j]]);
					vert.textureCoordinate = glm::vec2(textureCoords[vtIncides[j]]);
					vert.normal = glm::vec3(normals[vnIncides[j]]);

					// see if the vertex already exists in the vector of vertices
					if (std::find(vertices.begin(), vertices.end(), vert) != vertices.end())
					{
						// vertex already exists
						// get the position in the vector of vertices
						unsigned int pos = std::distance(vertices.begin(), std::find(vertices.begin(), vertices.end(), vert));
						// push that position back as an index for the indices vector
						indices.push_back(pos);
					}
					else
					{
						// if this is a new vertex
						// push the vertex back onto the vector
						vertices.push_back(vert);
						// push back the index for that vector to the indices
						indices.push_back(vertices.size() - 1);
					}
				}
			}

			// move the next start point to the end of the last line
			i = eol;
		}
		// push 3 floats for the position (x, y, z)
		layout.push<float>(3);
		// push 2 floats for the texture coords (x, y)
		layout.push<float>(2);
		// push 3 floats for the normals (x, y, z)
		layout.push<float>(3);
		// return the mesh
	}
	
}
}