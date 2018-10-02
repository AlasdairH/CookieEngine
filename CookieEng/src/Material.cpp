#include "Material.h"
namespace CookieEng
{
namespace Resource
{
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

	void Material::setMVP(const glm::mat4 &_m, const glm::mat4 &_v, const glm::mat4 &_p)
	{
		if (m_shaderProgram == nullptr)
		{
			LOG_ERROR("Unable to set MVP, shader not set");
			return;
		} 

		m_shaderProgram->bind();
		m_shaderProgram->setUniformMat4f("u_m", _m);
		m_shaderProgram->setUniformMat4f("u_v", _v);
		m_shaderProgram->setUniformMat4f("u_p", _p);
		//m_shaderProgram->unBind();
	}
}
}

