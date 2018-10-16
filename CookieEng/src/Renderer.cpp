
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

	void Renderer::drawToFrameBuffer(const FrameBuffer & _fbo, ECS::Entity & _entity)
	{
		if (!_entity.hasComponent<Components::Renderable>())
		{
			LOG_WARNING("Unable to draw, no renderable component found");
			return;
		}

		_fbo.bind();
		// cache the render component
		std::shared_ptr<Components::Renderable> renderComponent = _entity.getComponent<Components::Renderable>();
		// set the model matrix (view and projection is set by camera uniform buffer)
		renderComponent->getMaterial()->setModelMatrix(_entity.getComponent<Components::Transform>()->getMatrix());
		// use the material (shader)
		renderComponent->getMaterial()->use();
		// use the VAO (vertices)
		renderComponent->getVAO()->bind();
		// unse the IBO (vertex indices)
		renderComponent->getIBO()->bind();

		// render it to the bound buffer (should in theory be the designated famebuffer)
		glDrawElements(GL_TRIANGLES, renderComponent->getIBO()->getCount(), GL_UNSIGNED_INT, 0);

		_fbo.unBind();
	}
	
}
}
