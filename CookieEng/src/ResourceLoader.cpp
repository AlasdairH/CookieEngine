#include "ResourceLoader.h"

namespace CookieEng
{
namespace Core
{

	ResourceLoader::ResourceLoader()
	{

	}

	void ResourceLoader::fromFile(const std::string _filepath)
	{
		LOG_MESSAGE("Resource Loader: Starting Load");
		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();

		std::string text = Services::ServiceLocator::getFileManager().loadTextFile(_filepath);
		int lineNumber = 0;

		for (unsigned int i = 0; i < text.size(); ++i)
		{
			++lineNumber;
			// find the index of the next end of line char, starting from i
			unsigned int eol = text.find("\n", i);
			// get a substring from i, for end of line - i chars
			std::string line = text.substr(i, eol - i);

			// split the current line by the ' ' delimiter
			std::vector<std::string> splitString = Utilities::UtilsStr::split(line, ' ');

			if (splitString.size() == 0) continue;

			// LOAD
			if (splitString[0] == "LOAD")
			{
				// LOAD TEXTURE filepath name
				if (splitString[1] == "TEXTURE")
				{
					LOG_MESSAGE("Resource Loader: Loading Texture | " << splitString[2] << " | " << splitString[3]);
					resourceManager.load<Resources::Texture>(splitString[3], splitString[2]);
				}
				// LOAD SHADER filepath name
				else if (splitString[1] == "SHADER")
				{
					LOG_MESSAGE("Resource Loader: Loading Shader | " << splitString[2] << " | " << splitString[3] << " | " << splitString[4]);
					resourceManager.load<Resources::ShaderProgram>(splitString[3], splitString[2]);
				}
			}
			// CREATE
			else if (splitString[0] == "CREATE")
			{
				// CREATE MATERIAL filepath name
				if (splitString[1] == "MATERIAL")
				{
					LOG_MESSAGE("Resource Loader: Creating Material | " << splitString[2] << " | " << splitString[3]);
					resourceManager.load<Resources::Material>(splitString[3], splitString[2]);
				}
			}
			// SET
			else if (splitString[0] == "SET")
			{
				// SET MATERIAL
				if (splitString[1] == "MATERIAL")
				{
					// SET MATERIAL DIFFUSETEXTURE texture material
					if (splitString[2] == "DIFFUSETEXTURE")
					{
						// check texture and material exist
						if (resourceManager.exists(splitString[3]) && resourceManager.exists(splitString[4]))
						{
							resourceManager.get<Resources::Material>(splitString[4])->setDiffuse(splitString[3]);
							LOG_MESSAGE("Resource Loader: Set Material " << splitString[4] << " diffuse texture to " << splitString[3]);
						}
						else
						{
							LOG_ERROR("Resource Loader(LINE " << lineNumber << "): Unable to set DIFFUSETEXTURE, Material " << splitString[4] << " or " << splitString[3] << " does not exist");
						}
					}
				}
			}

			// move the cursor on to the next line
			i = eol;
		}

		LOG_MESSAGE("Resource Loader: Finished Load");
	}
}
}