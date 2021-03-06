#include "Shader.h"

namespace CookieEng
{
namespace Graphics
{

	Shader::Shader(ShaderType _shaderType)
	{
		m_shaderType = _shaderType;
		init();
	}

	void Shader::init()
	{
		m_shaderID = glCreateShader(m_shaderType);
		if (m_shaderType == SHADER_VERTEX)
		{
			LOG_MESSAGE("Created Vertex Shader with ID " << m_shaderID);
		}
		else if (m_shaderType == SHADER_FRAGMENT)
		{

			LOG_MESSAGE("Created Fragment Shader with ID " << m_shaderID);

		}
	}

	bool Shader::load(std::string _filepath)
	{
		m_verified = false;

		std::string text = Services::ServiceLocator::getFileManager().loadTextFile(_filepath);
		const char *rawText = text.c_str();

		glShaderSource(m_shaderID, 1, &rawText, NULL);
		glCompileShader(m_shaderID);

		if (verify())
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Shader::verify()
	{
		GLint result = GL_FALSE;
		int infoLogLength;

		// check the shader is valid and store the result
		glGetShaderiv(m_shaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(m_shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		// if the length is greater than 0, something went wrong :(
		if (infoLogLength > 0)
		{
			GLchar* log = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(m_shaderID, infoLogLength, NULL, log);
			std::cerr << "ERROR: Shader Compile failed: " << log << std::endl;
			delete[] log;

			return false;
		}
		m_verified = true;
		LOG_MESSAGE("Shader " << m_shaderID << " Successfully Verified");
		return true;
	}
}
}