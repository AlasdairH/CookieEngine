#pragma once

// cstdlib
#include <string>

// external libs
#include "GL/glew.h"
#include "external/stb_image/stb_image.h"

// program
#include "Macro.h"

namespace CookieEng
{
namespace Graphics
{
	/*! @class Texture
	*	@brief An abstraction of an OpenGL Texture
	*
	*	This class handles the loading (move this) and assignment of an OpenGL texture.
	*/
	class Texture
	{
	public:
		/** @brief Texture Ctor
		*	@param _filepath The path to the image to be loaded
		*
		*	Loads an image file using stb_image and loads it into OpenGL
		*/
		Texture(const std::string &_filepath);
		/** @brief Texture Dtor
		*
		*	Frees the OpenGL Texture
		*/
		~Texture();

		/** @brief Binds the Texture
		*	@param _slot The texture slot to bind the texture to
		*
		*	Binds the texture to a specific slot in the OpenGL texture slot array
		*/
		void bind(GLuint _slot = 0) const;
		/** @brief Uninds the Texture
		*
		*	Unbinds the texture.
		*/
		void unBind() { glBindTexture(GL_TEXTURE_2D, 0); }

		/** @brief Gets the with of the texture
		*	@return The texture width
		*
		*	Gets the with of the texture
		*/
		inline int getWidth() const { return m_width; }
		/** @brief Gets the with of the texture
		*	@return The texture height
		*
		*	Gets the height of the texture
		*/
		inline int getHeight() const { return m_height; }

	protected:
		GLuint m_textureID;				/**< The OpenGL Texture ID */
		std::string m_filepath;			/**< The filepath to the texture */
		unsigned char *m_localBuffer;	/**< The local buffer for the loaded image */

		int m_width, m_height, m_BPP;	/**< The width, height and bpp */
	};
}
}