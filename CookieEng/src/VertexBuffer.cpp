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
		LOG_MESSAGE("Vertex Buffer Object with ID: " << m_vertexBufferID << " Created");
	}

	void VertexBuffer::loadData(const void *_data, GLuint _count, GLuint _size)
	{
		m_count = _count;
		bind();
		// TODO: Fix static draw
		glBufferData(m_vertexBufferType, _size, _data, GL_STATIC_DRAW);
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