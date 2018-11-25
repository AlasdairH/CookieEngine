
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

	void Renderer::draw(ECS::Entity & _entity)
	{
		bool hasRenderable = _entity.hasComponent<Components::Renderable>();
		bool hasGUI = _entity.hasComponent<Components::GUI::UIButton>();

		std::shared_ptr<Components::Transform> transformComponent = _entity.getComponent<Components::Transform>();

		if (hasRenderable)
		{
			// cache the render component
			std::shared_ptr<Components::Renderable> renderComponent = _entity.getComponent<Components::Renderable>();
			// cache the transform component

			// set the model matrix (view and projection is set by camera uniform buffer)
			renderComponent->getMaterial()->setModelMatrix(transformComponent->getMatrix());
			// use the material (shader)
			renderComponent->getMaterial()->use();
			// use the VAO (vertices)
			renderComponent->getMesh()->getVAO()->bind();
			// unse the IBO (vertex indices)
			renderComponent->getMesh()->getIBO()->bind();

			if (m_renderMode == CNG_RENDERMODE_WIREFRAME)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}

			// render it to the bound buffer (should in theory be the designated famebuffer)
			glDrawElements(GL_TRIANGLES, renderComponent->getMesh()->getIBO()->getCount(), GL_UNSIGNED_INT, 0);

			if (m_renderMode == CNG_RENDERMODE_WIREFRAME)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
		}

		if (hasGUI)
		{
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_CULL_FACE);

			std::shared_ptr<Components::GUI::UIButton> button = _entity.getComponent<Components::GUI::UIButton>();
			// set the model matrix (view and projection is set by camera uniform buffer)
			button->getMaterial()->setModelMatrix(transformComponent->getMatrix());
			// use the material (shader)
			button->getMaterial()->use();
			// use the VAO (vertices)
			button->getVAO()->bind();
			// unse the IBO (vertex indices)
			button->getIBO()->bind();

			glDrawElements(GL_TRIANGLES, button->getIBO()->getCount(), GL_UNSIGNED_INT, 0);

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
		}
	}
	
}
}
