#include "ShaderProgram.h"

namespace CookieEng
{
namespace Resources
{

	ShaderProgram::ShaderProgram()
	{
		// create the program to store the shaders
		m_programID = glCreateProgram();
		LOG_MESSAGE("Created Shader Program with ID " << m_programID);

		m_verified = false;
	}

	void ShaderProgram::load(const std::string &_name, const std::string &_filepath)
	{
		if (_filepath == "")
		{
			LOG_MESSAGE("Creating Material with Default Settings");
			return;
		}
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
				if (splitString[1] != "shaderprogram")
				{
					LOG_ERROR("Tried to load ShaderProgram from a file that isn't a ShaderProgram");
				}
			}
			// VERTEX
			else if (splitString[0] == "VERTEX")
			{
				Graphics::Shader shader(Graphics::SHADER_VERTEX);
				shader.load(splitString[1]);
				attachShader(shader);
			}
			// FRAGMENT
			else if (splitString[0] == "FRAGMENT")
			{
				Graphics::Shader shader(Graphics::SHADER_FRAGMENT);
				shader.load(splitString[1]);
				attachShader(shader);
			}
			// LINK
			else if (splitString[0] == "LINK")
			{
				link();
			}

			// move the cursor on to the next line
			i = eol;
		}
	}

	void ShaderProgram::attachShader(Graphics::Shader &_shader)
	{
		glAttachShader(m_programID, _shader.getShaderID());
	}

	void ShaderProgram::link()
	{
		glLinkProgram(m_programID);

		verify();
	}

	bool ShaderProgram::verify()
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

	void ShaderProgram::bind() const
	{
		if (m_verified)
		{
			glUseProgram(m_programID);
		}
		else
		{
			LOG_ERROR("Bind Failed, Shader Program not Verified");
			assert(m_verified);
		}
	}
	void ShaderProgram::unBind() const
	{
		glUseProgram(0);
	}
	int ShaderProgram::getUniformLocation(const std::string & _name)
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

	void ShaderProgram::setUniform1f(const std::string & _name, float _value)
	{
		glUniform1f(getUniformLocation(_name), _value);
	}

	void ShaderProgram::setUniform3f(const std::string & _name, float _value1, float _value2, float _value3)
	{
		glUniform3f(getUniformLocation(_name), _value1, _value2, _value3);
	}

	void ShaderProgram::setUniform4f(const std::string &_name, float _value1, float _value2, float _value3, float _value4)
	{
		glUniform4f(getUniformLocation(_name), _value1, _value2, _value3, _value4);
	}

	void ShaderProgram::setUniform1i(const std::string & _name, int _value)
	{
		glUniform1i(getUniformLocation(_name), _value);
	}

	void ShaderProgram::setUniformMat4f(const std::string & _name, const glm::mat4 &_value)
	{
		glUniformMatrix4fv(getUniformLocation(_name), 1, GL_FALSE, &_value[0][0]);
	}

	void ShaderProgram::setUniformBool(const std::string & _name, const bool _value)
	{
		setUniform1i(_name, _value);
	}
}
}