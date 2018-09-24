#include "..\include\Texture.h"

namespace CookieEng
{
namespace Graphics
{

	Texture::Texture(const std::string & _filepath)
		: m_textureID(0), m_filepath(_filepath), m_localBuffer(nullptr), m_width(0), m_height(0), m_BPP(0)
	{
		// load the image
		stbi_set_flip_vertically_on_load(true);
		m_localBuffer = stbi_load(_filepath.c_str(), &m_width, &m_height, &m_BPP, 4);
		LOG_MESSAGE("Loaded File: " << _filepath);

		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		// minification filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// magnification filter
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		// give OpenGL the data
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
		unBind();

		// free the image now it is stored on the GPU
		if (m_localBuffer)
		{
			stbi_image_free(m_localBuffer);
		}

		LOG_MESSAGE("Created Texture with ID: " << m_textureID);
	}

	Texture::~Texture()
	{
		LOG_MESSAGE("Destroyed Texture with ID: " << m_textureID);
		glDeleteTextures(1, &m_textureID);
	}

	void Texture::bind(GLuint _slot) const
	{
		glActiveTexture(GL_TEXTURE0 + _slot);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

	}

}
}



