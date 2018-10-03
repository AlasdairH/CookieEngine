
#include "..\include\Renderer.h"
namespace CookieEng
{
namespace Graphics
{
	Renderer::Renderer()
	{
		m_frameBuffer = nullptr;
		LOG_MESSAGE("Renderer Created");
	}

	void Renderer::drawToFrameBuffer(const FrameBuffer &_fbo, const VertexArray & _vao, const VertexBuffer & _indexBuffer, const Resources::Material & _material)
	{
		_fbo.bind();
		_material.use();
		_vao.bind();
		_indexBuffer.bind();

		glDrawElements(GL_TRIANGLES, _indexBuffer.getCount(), GL_UNSIGNED_INT, 0);

		_fbo.unBind();

		// if the program is in debug mode...
		// this is to enhance performance on release builds
#ifdef DEBUG
		_material.unUse();
		_vao.unBind();
		_indexBuffer.unBind();
#endif
	}
	
}
}
