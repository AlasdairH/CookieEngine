#include "Material.h"
namespace CookieEng
{
namespace Resources
{
	void Material::load(const std::string & _name, const std::string & _filepath)
	{
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

			// FILETYPE
			if (splitString[0] == "FILETYPE")
			{
				// FILETYPE type
				if (splitString[1] != "Material")
				{
					LOG_ERROR("Tried to load ShaderProgram from a file that isn't a ShaderProgram");
				}
			}
			// SET
			else if (splitString[0] == "SET")
			{
				// SET SHADER
				if (splitString[1] == "SHADER")
				{
					setShader(splitString[2]);
				}
				// SET DIFFUSE
				if (splitString[1] == "DIFFUSE")
				{
					setDiffuse(splitString[2]);
				}
			}

			// move the cursor on to the next line
			i = eol;
		}
	}
	
	void Material::use() const
	{
		m_shaderProgram->bind();

		if (m_textureDiffuse != nullptr)
		{
			m_textureDiffuse->bind(0);
		}
	}
	void Material::unUse() const
	{
		m_shaderProgram->unBind();

		if (m_textureDiffuse != nullptr)
		{
			m_textureDiffuse->unBind();
		}
	}

	void Material::setShader(const std::string _resMgr_shaderName)
	{
		ResMgmt::ResourceManager &resMgr = ResMgmt::ResourceManager::getInstance();
		m_shaderProgram = resMgr.get<ShaderProgram>(_resMgr_shaderName);
	}

	void Material::setDiffuse(const std::string _resMgr_textureName)
	{
		if (m_shaderProgram == nullptr)
		{
			LOG_ERROR("Unable to set Material diffuse, shader not set");
			return;
		}
		// get the diffuse texture from the resource manager and set the material texture
		ResMgmt::ResourceManager &resMgr = ResMgmt::ResourceManager::getInstance();
		m_textureDiffuse = resMgr.get<Texture>(_resMgr_textureName);
		m_shaderProgram->bind();
		// set up the uniforms on the shader
		m_shaderProgram->setUniform1i("u_texture", 0);
		m_shaderProgram->setUniformBool("u_useTexture", true);
		m_shaderProgram->unBind();
	}

	void Material::setDiffuse(const glm::vec4 & _colour)
	{
		if (m_shaderProgram == nullptr)
		{
			LOG_ERROR("Unable to set Material diffuse, shader not set");
			assert(m_shaderProgram != nullptr);
			return;
		}
		m_diffuseColour = _colour;

		m_shaderProgram->setUniform4f("u_diffuse", m_diffuseColour.r, m_diffuseColour.g, m_diffuseColour.b, m_diffuseColour.a);
		m_shaderProgram->setUniformBool("u_useTexture", false);

		m_textureDiffuse = nullptr;
	}

	void Material::setModelMatrix(const glm::mat4 &_m)
	{
		if (m_shaderProgram == nullptr)
		{
			LOG_ERROR("Unable to set MVP, shader not set");
			return;
		} 
		 
		m_shaderProgram->bind();
		m_shaderProgram->setUniformMat4f("u_m", _m);
		m_shaderProgram->unBind();
	}
}
}

