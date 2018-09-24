#include "ResourceManager.h"

namespace CookieEng
{
namespace Core
{
	ResourceManager::ResourceManager()
	{

	}

	ResourceManager::~ResourceManager()
	{
		LOG_MESSAGE("Removing Textures from Resource Manager");
		// remove textures
		std::map<std::string, std::shared_ptr<Graphics::Texture>>::iterator it1;
		for (it1 = m_textureMap.end(); it1 != m_textureMap.end(); --it1)
		{
			m_textureMap[it1->first].reset();
			m_textureMap.erase(it1->first);
		}
		LOG_MESSAGE("Removing Shaders from Resource Manager");
		// remove shader programs
		std::map<std::string, std::shared_ptr<Graphics::ShaderProgram>>::iterator it2;
		for (it2 = m_shaderProgramMap.end(); it2 != m_shaderProgramMap.end(); --it2)
		{
			m_shaderProgramMap[it2->first].reset();
			m_shaderProgramMap.erase(it2->first);
		}
		LOG_MESSAGE("Removing Materials from Resource Manager");
		// remove materials
		std::map<std::string, std::shared_ptr<Core::Material>>::iterator it3;
		for (it3 = m_materialMap.end(); it3 != m_materialMap.end(); --it3)
		{
			m_materialMap[it3->first].reset();
			m_materialMap.erase(it3->first);
		}
	}

	// TEXTURE
	void ResourceManager::loadTexture(const std::string _filepath, const std::string _name)
	{
		// check if texture name is unique
		if (textureExists(_name))
		{
			LOG_ERROR("Texture " << _name << " already exists in Resource Manager");
			return;
		}
		// if texture name not found in map
		else
		{
			m_textureMap.insert(std::make_pair(_name, std::make_shared<Graphics::Texture>(_filepath)));
			LOG_MESSAGE("Loaded Texture: " << _name << " to Resource Manager");
		}
	}

	void ResourceManager::removeTexture(const std::string _name)
	{
		// check if texture name is unique
		if (textureExists(_name))
		{
			LOG_ERROR("Removing Texutre " << _name << " from Resource Manager");
			m_textureMap.erase(_name);
		}
		// if texture name not found in map
		else
		{
			LOG_MESSAGE("Unable to remove Texture " << _name << " from Resource Manager, it does not exist");
		}
	}

	std::shared_ptr<Graphics::Texture> ResourceManager::getTexture(std::string _name)
	{
		if (textureExists(_name))
		{
			return m_textureMap[_name];
		}
		else
		{
			LOG_ERROR("Texture: " << _name << " Not Found in Resource Manager");
			return m_textureMap["Default"];
		}
	}

	bool ResourceManager::textureExists(const std::string _name)
	{
		if (m_textureMap.find(_name) != m_textureMap.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	// SHADER PROGRAM
	void ResourceManager::loadShaderProgram(const std::string _filepathVert, const std::string _filepathFrag, const std::string _name)
	{
		// check if shader name is unique
		if (m_shaderProgramMap.find(_name) != m_shaderProgramMap.end())
		{
			LOG_ERROR("Shader Program" << _name << " already exists in Resource Manager");
			return;
		}
		// if shader name not found in map
		else
		{
			m_shaderProgramMap.insert(std::make_pair(_name, std::make_shared<Graphics::ShaderProgram>(_filepathVert, _filepathFrag)));
			LOG_MESSAGE("Loaded Shader Program: " << _name << " to Resource Manager");
		}
	}

	std::shared_ptr<Graphics::ShaderProgram> ResourceManager::getShaderProgram(std::string _name)
	{
		if (shaderExists(_name))
		{
			return m_shaderProgramMap[_name];
		}
		else
		{
			LOG_ERROR("Shader Program: " << _name << " not found in Resource Manager");
			return m_shaderProgramMap["Default"];
		}
	}

	bool ResourceManager::shaderExists(const std::string _name)
	{
		if (m_shaderProgramMap.find(_name) != m_shaderProgramMap.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// MATERIAL
	void ResourceManager::createMaterial(const std::string _shaderProgram, const std::string _name)
	{

		// check requested shader program exists
		if (m_shaderProgramMap.find(_shaderProgram) == m_shaderProgramMap.end()) 
		{
			LOG_ERROR("Unable to create Material " << _name << ", requested shader " << _shaderProgram << " does not exist in Resource Manager");
			return;
		}
		else 
		{
			// add new material to map
			m_materialMap.insert(std::make_pair(_name, std::make_shared<Core::Material>()));
			// set materials shader
			m_materialMap[_name]->setShader(_shaderProgram);
		}
		LOG_MESSAGE("Loaded Material: " << _name << " to Resource Manager");
	}

	std::shared_ptr<Core::Material> ResourceManager::getMaterial(std::string _name)
	{
		if (materialExists(_name))
		{
			return m_materialMap[_name];
		}
		else
		{
			LOG_ERROR("Material: " << _name << " not found in Resource Manager");
			return m_materialMap["Default"];
		}
	}

	bool ResourceManager::materialExists(const std::string _name)
	{
		if (m_materialMap.find(_name) != m_materialMap.end())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
}