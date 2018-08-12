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
}
}