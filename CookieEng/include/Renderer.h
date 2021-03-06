#pragma once

// cstdlib
#include <string>
#include <iostream>
#include <vector>

// external libs
#include "GL/glew.h"

// program
#include "Entity.h"
#include "Renderable.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Material.h"
#include "FrameBuffer.h"
#include "Transform.h"
#include "UIButton.h"


namespace CookieEng
{
namespace Graphics
{

	enum RenderMode { CNG_RENDERMODE_FILL, CNG_RENDERMODE_WIREFRAME};

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

		/** @brief Sets the rendermode for the renderer
		*	@param _renderMode The rendermode to set
		*
		*	Sets the rendermode
		*/
		inline void setRenderMode(RenderMode _renderMode) { m_renderMode = _renderMode; }

		/** @brief Sets the default FrameBuffer to render to if one has not been provided.
		*	@param _frameBuffer A pointer to the FrameBuffer to use
		*
		*	Sets the default FrameBuffer to render to if one has not been provided. CAREFUL OF DANGLING POINTERS HERE
		*/
		inline void setFrameBuffer(FrameBuffer *_frameBuffer) { m_frameBuffer = _frameBuffer; }

		/** @brief Draw to a framebuffer
		*	@param _fbo The framebuffer to draw to
		*	@param _vao The VertexArray that contains the vertex data for the model to be displayed.
		*	@param _indexBuffer The index buffer (VertexBuffer) that contains the indicies to map the vertex drawing to. (Avoids duplicate data)
		*	@param _material The material to use when rendering the mesh to the screen
		*
		*	Takes a frame buffer and the required objects for rendering and renders using the provided material to the framebuffer. 
		*/
		void drawToFrameBuffer(const FrameBuffer &_fbo, const VertexArray &_vao, const VertexBuffer &_indexBuffer, const Resources::Material &_material);

		/** @brief Draw to the currently bound framebuffer
		*	@param _entity The Entity to draw
		*
		*	Takes the required objects for rendering and renders using the provided material to the currently bound framebuffer.
		*/
		void draw(ECS::Entity &_entity);

	protected:
		FrameBuffer *m_frameBuffer;		/**< The framebuffer to render to by default */

		RenderMode	m_renderMode = CNG_RENDERMODE_FILL;		/**< The render mode to use when drawing */
	};

}
}
