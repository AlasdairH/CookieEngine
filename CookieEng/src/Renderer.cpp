
#include "..\include\Renderer.h"
namespace CookieEng
{
namespace Graphics
{
	Renderer::Renderer()
	{
		LOG_MESSAGE("Renderer Created");
	}

	void Renderer::draw(const VertexArray & _vao, const VertexBuffer & _indexBuffer, const Program & _shaderProgram)
	{
		_shaderProgram.bind();
		_vao.bind();
		_indexBuffer.bind();

		glDrawElements(GL_TRIANGLES, _indexBuffer.getCount(), GL_UNSIGNED_INT, 0);

		// if the program is in debug mode...
		// this is to enhance performance on release builds
#ifdef DEBUG
		_shaderProgram.unBind();
		_vao.unBind();
		_indexBuffer.unBind();
#endif
	}
	
}
}
