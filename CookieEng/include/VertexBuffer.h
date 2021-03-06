#pragma once

// cstdlib
#include <string>
#include <iostream>
#include <vector>

// external libs
#include "GL/glew.h"

// program
#include "ServiceLocator.h"

namespace CookieEng
{
namespace Graphics
{

	enum VertexBufferType { CNG_BUFFER_ARRAY = GL_ARRAY_BUFFER, CNG_BUFFER_ELEMENT_ARRAY = GL_ELEMENT_ARRAY_BUFFER, CNG_BUFFER_UNIFORM = GL_UNIFORM_BUFFER };

	/*! @class VertexBuffer
	*	@brief An abstraction of an OpenGL Vertex Bufer Object (VBO).
	*
	*	An anstraction of the OpenGL Vertex Buffer Object (VBO). This is used by the VertexArray class along with a VertexBufferLayout for drawing objects.
	*/
	class VertexBuffer
	{
	public:
		/** @brief Vertex Buffer Ctor
		*	@param _type The VBO type to create
		*
		*	Generates a Vertex Buffer Object (VBO) for use by OpenGL of the specified type.
		*/
		VertexBuffer(const VertexBufferType _type);
		/** @brief Vertex Buffer Ctor
		*	@param _type The VBO type to create
		*	@param _data The data to send to the VBO
		*	@param _count The number of items of data
		*	@param _size The size of the data in bytes
		*
		*	Generates a Vertex Buffer Object (VBO) through the init() method for use by OpenGL of the specified type. Also sends the specified data to the VBO with the size provided.
		*/
		VertexBuffer(const VertexBufferType _type, const void *_data, GLuint _count, GLuint _size);
		/** @brief Vertex Buffer Dtor
		*
		*	Deletes the Vertex Buffer
		*/
		~VertexBuffer();

		/** @brief
		*
		*	Generates the VBO. This is done through this method to avoid issues of using OpenGL calls in constructors.
		*/
		void init();

		/** @brief Loads data to the VBO.
		*	@param _data he data to send to the VBO
		*	@param _count The number of items of data
		*	@param _size The size of the data in bytes
		*
		*	Loads data to the VBO.
		*/
		void loadData(const void *_data, GLuint _count, GLuint _size);

		/** @brief Returns the count of the number of items contained within the buffer.
		*
		*	Returns the count of the number of items contained within the buffer.
		*/
		inline GLuint getCount() const { return m_count; }

		/** @brief Binds the VBO.
		*
		*	Binds the VBO.
		*/
		void bind() const;
		/** @brief Unbinds the VBO.
		*
		* Unbinds the VBO.
		*/
		void unBind() const;

		/** @brief Bind the buffer to an indexed buffer target
		*	@param _index The index of the binding point
		*
		*	Binds the buffer object buffer to the binding point at index index of the array of targets specified by target. (Copied from Kkronos.org)
		*/
		void bindBase(GLuint _index);

	protected:
		VertexBufferType	m_vertexBufferType;			/**< The type of Vertex Buffer (BUFFER_ARRAY, BUFFER_ELEMENT_ARRAY, etc)  */
		GLuint				m_count;					/**< The number of items of data there is in the buffer */
		GLuint				m_vertexBufferID;			/**< The Vertex Buffer ID */

		GLuint				m_usage = GL_STATIC_DRAW;	/**< The usage pattern for the buffer */
	};

}
}
