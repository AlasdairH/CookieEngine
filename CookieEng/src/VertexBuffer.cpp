#include "VertexBuffer.h"

namespace CookieEng
{
namespace Graphics
{

	VertexBuffer::VertexBuffer(const VertexBufferType _type)
	{
		m_vertexBufferType = _type;
		init();
	}

	VertexBuffer::VertexBuffer(const VertexBufferType _type, const void *_data, GLuint _count, GLuint _size)
	{
		m_vertexBufferType = _type;
		init();
		loadData(_data, _count, _size);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_vertexBufferID);
		LOG_MESSAGE("Vertex Buffer Object with ID: " << m_vertexBufferID << " Deleted");
	}

	void VertexBuffer::init()
	{
		glGenBuffers(1, &m_vertexBufferID);

		// try to guess what the usage pattern will be, can be set otherwise
		if (m_vertexBufferType == CNG_BUFFER_ARRAY || m_vertexBufferType == CNG_BUFFER_ELEMENT_ARRAY)
		{
			m_usage = GL_STATIC_DRAW;
		}
		else if (m_vertexBufferType == CNG_BUFFER_UNIFORM)
		{
			m_usage = GL_DYNAMIC_DRAW;
		}

		LOG_MESSAGE("Vertex Buffer Object with ID: " << m_vertexBufferID << " Created");
	}

	void VertexBuffer::loadData(const void *_data, GLuint _count, GLuint _size)
	{
		m_count = _count;
		bind();
		glBufferData(m_vertexBufferType, _size, _data, m_usage);
	}

	void VertexBuffer::bind() const
	{
		glBindBuffer(m_vertexBufferType, m_vertexBufferID);
	}

	void VertexBuffer::unBind() const
	{
		glBindBuffer(m_vertexBufferType, 0);
	}

	void VertexBuffer::bindBase(GLuint _index)
	{
		// TODO: Might not be a uniform buffer?
		glBindBufferBase(GL_UNIFORM_BUFFER, _index, m_vertexBufferID);
	}

}
}