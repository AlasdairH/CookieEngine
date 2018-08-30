#pragma once

// cstdlib
#include <string>
#include <iostream>
#include <vector>

// external libs
#include "GL/glew.h"

// program
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ShaderProgram.h"
#include "FrameBuffer.h"

namespace CookieEng
{
namespace Graphics
{
	/*! @class Renderer
	*	@brief An OpenGL Renderer
	*
	*	This renderer uses OpenGL to display a VertexArray with an accompanything shader (material in future).
	*/
	class Renderer
	{
	public:
		/** @brief Program Ctor
		*
		*	Logs a created message
		*/
		Renderer();

		// TODO: Do I need this? / Doxygen
		inline void setFrameBuffer(FrameBuffer *_frameBuffer) { m_frameBuffer = _frameBuffer; }

		// TODO: Update to Material
		/** @brief Program Ctor
		*	@param _vao The VertexArray that contains the vertex data for the model to be displayed.
		*	@param _indexBuffer The index buffer (VertexBuffer) that contains the indicies to map the vertex drawing to. (Avoids duplicate data)
		*	@param _shaderProgram The shader program to use to actually render the triangles to the screen
		*
		*	Creates a shader program and sets the verified status to false.
		*/
		void drawToFrameBuffer(const FrameBuffer &_fbo, const VertexArray &_vao, const VertexBuffer &_indexBuffer, const ShaderProgram &_shaderProgram);
	protected:
		FrameBuffer *m_frameBuffer; // TODO: Doxygen
	};

}
}
