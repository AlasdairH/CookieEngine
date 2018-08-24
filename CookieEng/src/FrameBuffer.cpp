#include "FrameBuffer.h"

namespace CookieEng
{
namespace Graphics
{

	FrameBuffer::FrameBuffer(const int _width, const int _height)
	{
		LOG_MESSAGE("Creating Frame Buffer...");
		m_width = _width;
		m_height = _height;

		// create VAO
		m_arrayBuffer = new VertexArray;
		// create VBO
		m_vertexBuffer = new VertexBuffer(Graphics::BUFFER_ARRAY);
		GLfloat fbo_vertices[] = 
		{
			-1.0f,  1.0f,  0.0f, 1.0f,
			-1.0f, -1.0f,  0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,

			-1.0f,  1.0f,  0.0f, 1.0f,
			 1.0f, -1.0f,  1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f
		};
		// create layout
		Graphics::VertexBufferLayout layout1;
		// push 2 floats to the layout (x and y pos)
		layout1.push<float>(2);
		// push 2 floats to the layout (x and y tex coord)
		layout1.push<float>(2);
		m_arrayBuffer->addBuffer(*m_vertexBuffer, layout1);
		m_vertexBuffer->loadData(&fbo_vertices, 0, sizeof(fbo_vertices));

		m_shaderProgram = new ShaderProgram("resources/shaders/PostProcVert.glsl", "resources/shaders/PostProcFrag.glsl");

		glGenFramebuffers(1, &m_frameBufferID);
		bind();
		

		createTextureAttachment();
		//createDepthTextureAttachment();
		createDepthRenderBufferAttachment();

		// Set the list of draw buffers.
		//GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
		//glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

		GLenum status;
		if ((status = glCheckFramebufferStatus(GL_FRAMEBUFFER)) != GL_FRAMEBUFFER_COMPLETE) 
		{
			LOG_ERROR("Could not Create FrameBuffer: " << status);
		}
		else
		{
			LOG_MESSAGE("Created Frame Buffer with ID: " << m_frameBufferID);
		}


		unBind();
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &m_frameBufferID);
		glDeleteTextures(1, &m_textureID);
		glDeleteRenderbuffers(1, &m_depthRenderBufferID);
		delete m_vertexBuffer;

	}

	void FrameBuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
	}

	void FrameBuffer::unBind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // back to default
		//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void FrameBuffer::drawToScreen()
	{
		m_shaderProgram->bind();
		m_arrayBuffer->bind();
		

		glBindTexture(GL_TEXTURE_2D, m_textureID);
		m_shaderProgram->setUniform1i("screenTexture", 0);

		glDisable(GL_DEPTH_TEST);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glEnable(GL_DEPTH_TEST);

#ifdef DEBUG
		m_shaderProgram->unBind();
		m_arrayBuffer->unBind();
#endif
	}

	void FrameBuffer::createTextureAttachment()
	{
		bind();
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// attach the texture to the framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureID, 0);
	}

	void FrameBuffer::createDepthRenderBufferAttachment()
	{
		bind();
		glGenRenderbuffers(1, &m_depthRenderBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_depthRenderBufferID);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);

		// attach the renderbuffer to the framebuffer
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderBufferID);
	}
}
}