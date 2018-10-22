#include "Transform.h"

namespace CookieEng
{
namespace Components
{

	Transform::Transform()
	{
		m_translationMatrix = glm::mat4(1.0f);
		m_rotationMatrix = glm::mat4(1.0f);
		m_scaleMatrix = glm::mat4(1.0f);

		m_position = glm::vec3(0, 0, 0);
		m_rotation = glm::vec3(0, 0, 0);

		setModelMatrix();
	}

	void Transform::setModelMatrix()
	{
		m_modelMatrix = m_translationMatrix * m_rotationMatrix * m_scaleMatrix;
		m_modelMatrixNS = m_translationMatrix * m_rotationMatrix;
	}

	void Transform::setPosition(const glm::vec3 & _position)
	{
		m_position = _position;
		m_translationMatrix = glm::translate(glm::mat4(1.0), _position);
		setModelMatrix();
	}

	void Transform::translate(const glm::vec3 &_position)
	{
		m_position += _position; 
		m_translationMatrix = glm::translate(glm::mat4(1.0f), m_position);
		setModelMatrix();
	}

	void Transform::setRotation(const float _rotation, const glm::vec3 & _axis)
	{
		if (_axis.x)
		{
			m_rotation.x = _rotation;
			m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), _axis);
			m_rotationMatrix = glm::rotate(m_rotationMatrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
			m_rotationMatrix = glm::rotate(m_rotationMatrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
		}
		if (_axis.y)
		{
			m_rotation.y = _rotation;

			m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
			m_rotationMatrix = glm::rotate(m_rotationMatrix, glm::radians(_rotation), _axis);
			m_rotationMatrix = glm::rotate(m_rotationMatrix, glm::radians(m_rotation.z), glm::vec3(0, 0, 1));
		}
		if (_axis.z)
		{
			m_rotation.z = _rotation;
			m_rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.x), glm::vec3(1, 0, 0));
			m_rotationMatrix = glm::rotate(m_rotationMatrix, glm::radians(m_rotation.y), glm::vec3(0, 1, 0));
			m_rotationMatrix = glm::rotate(m_rotationMatrix, glm::radians(_rotation), _axis);
		}

		setModelMatrix();
	}

	void Transform::rotate(const float _rotation, const glm::vec3 _axis)
	{
		if (_axis.x)
		{
			m_rotation.x += _rotation;
		}
		if (_axis.y)
		{
			m_rotation.y += _rotation;
		}
		if (_axis.z)
		{
			m_rotation.z += _rotation;
		}

		m_rotationMatrix = glm::rotate(m_rotationMatrix, glm::radians(_rotation), _axis);

		setModelMatrix();
	}

	void Transform::onUpdate()
	{
		rotate(30.0f * CNG_DELTA_TIME, glm::vec3(1, 1, 1));
	}
}
}
