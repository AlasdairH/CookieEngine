#include "FileManager.h"

namespace CookieEng
{
namespace Services
{

	FileManager::FileManager()
	{

	}

	FileManager::~FileManager()
	{

	}

	std::string FileManager::loadTextFile(std::string _filepath)
	{
		std::ifstream inFile;
		//open the input file
		inFile.open(_filepath);

		if ((inFile.rdstate() & std::ifstream::failbit) != 0)
		{
			LOG_ERROR("Failed to Open File: " << _filepath);
		}
		else
		{
			LOG_MESSAGE("Loaded File: " << _filepath);
		}

		std::stringstream strStream;
		// read the file
		strStream << inFile.rdbuf();
		// store the string
		std::string str = strStream.str();

		return str;
	}

	// TODO: texture coords
	Data::Mesh FileManager::loadMesh(std::string _filepath)
	{
		Data::Mesh mesh;

		std::string objFile = loadTextFile(_filepath);

		unsigned int cursor = 0;
		

		for (unsigned int i = 0; i < objFile.size(); ++i)
		{
			// find the index of the next end of line char, starting from i
			unsigned int eol = objFile.find("\n", i);
			// get a substring from i, for end of line - i chars
			std::string line = objFile.substr(i, eol - i);

			// vertex line
			if (line.find("v ") != std::string::npos)
			{
				unsigned int firstSpaceIndex = line.find(" ", 0);
				unsigned int secondSpaceIndex = line.find(" ", firstSpaceIndex + 1);
				unsigned int thirdSpaceIndex = line.find(" ", secondSpaceIndex + 1);
				unsigned int eolIndex = line.find("\n", i);

				std::string xVal = line.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1);
				std::string yVal = line.substr(secondSpaceIndex + 1, thirdSpaceIndex - secondSpaceIndex - 1);
				std::string zVal = line.substr(thirdSpaceIndex + 1, eolIndex - thirdSpaceIndex - 1);
				
				Vertex v;
				v.position = glm::vec3(std::stof(xVal), std::stof(yVal), std::stof(zVal));

				mesh.vertices.push_back(v);
			}

			// face line
			if (line.find("f ") != std::string::npos)
			{
				unsigned int firstSpaceIndex = line.find(" ", 0);
				unsigned int secondSpaceIndex = line.find(" ", firstSpaceIndex + 1);
				unsigned int thirdSpaceIndex = line.find(" ", secondSpaceIndex + 1);
				unsigned int eolIndex = line.find("\n", i);

				std::string val1 = line.substr(firstSpaceIndex + 1, secondSpaceIndex - firstSpaceIndex - 1);
				std::string val2 = line.substr(secondSpaceIndex + 1, thirdSpaceIndex - secondSpaceIndex - 1);
				std::string val3 = line.substr(thirdSpaceIndex + 1, eolIndex - thirdSpaceIndex - 1);

				std::istringstream val1SS(val1);
				std::istringstream val2SS(val2);
				std::istringstream val3SS(val3);

				std::string vertexIndex1;
				std::getline(val1SS, vertexIndex1, '/');

				std::string vertexIndex2;
				std::getline(val2SS, vertexIndex2, '/');

				std::string vertexIndex3;
				std::getline(val3SS, vertexIndex3, '/');

				// -1 to correct for .obj starting from 1, where as OpenGL buffers start from 0
				mesh.indices.push_back(std::stoul(vertexIndex1) - 1);
				mesh.indices.push_back(std::stoul(vertexIndex2) - 1);
				mesh.indices.push_back(std::stoul(vertexIndex3) - 1);
			}

			// move the next start point to the end of the last line
			i = eol;
		}
		

		return mesh;
	}
}
}

