#include "Program.h"

namespace CookieEng
{
namespace Graphics
{

	Program::Program()
	{
		// create the program to store the shaders
		m_programID = glCreateProgram();
		LOG_MESSAGE("Created Shader Program with ID " << m_programID);

		m_verified = false;
	}

	void Program::attachShader(Shader &_shader)
	{
		glAttachShader(m_programID, _shader.getShaderID());
	}

	void Program::link()
	{
		glLinkProgram(m_programID);

		verify();
	}

	bool Program::verify()
	{
		GLint result = GL_FALSE;
		int infoLogLength;

		glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
		glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		if (infoLogLength > 0)
		{
			GLchar* log = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(m_programID, infoLogLength, &infoLogLength, log);
			LOG_ERROR("ERROR: Program Shader linking failed: " << log);
			delete[] log;

			return false;
		}

		LOG_MESSAGE("Shader Program " << m_programID << " Successfully Verified");

		m_verified = true;
		return true;
	}

	void Program::bind() const
	{
		if (m_verified)
		{
			glUseProgram(m_programID);
		}
		else
		{
			LOG_ERROR("Bind Failed, Shader Program not Verified");
		}
	}
	void Program::unBind() const
	{
		glUseProgram(0);
	}
	int Program::getUniformLocation(const std::string & _name)
	{
		if (m_uniformLocationCache.find(_name) != m_uniformLocationCache.end())
			return m_uniformLocationCache[_name];

		int location = glGetUniformLocation(m_programID, _name.c_str());
		if (location == -1)
		{
			LOG_WARNING("Uniform name " << _name << " does not exist!");
		}

		m_uniformLocationCache[_name] = location;

		return location;
	}

	void Program::setUniform1f(const std::string & _name, float _value)
	{
		glUniform1f(getUniformLocation(_name), _value);
	}

	void Program::setUniform4f(const std::string &_name, float _value1, float _value2, float _value3, float _value4)
	{
		glUniform4f(getUniformLocation(_name), _value1, _value2, _value3, _value4);
	}

	void Program::setUniform1i(const std::string & _name, int _value)
	{
		glUniform1f(getUniformLocation(_name), _value);
	}

	void Program::setUniformMat4f(const std::string & _name, const glm::mat4 &_value)
	{
		glUniformMatrix4fv(getUniformLocation(_name), 1, GL_FALSE, &_value[0][0]);
	}
}
}