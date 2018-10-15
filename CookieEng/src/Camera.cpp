#include "Camera.h"

namespace CookieEng
{
namespace Object
{
	Camera::Camera()
	{
		m_fov = 0.7f;
		m_aspect = 1.0f;

		glGenBuffers(1, &m_UBO);
		glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
		glBufferData(GL_UNIFORM_BUFFER, sizeof(m_uniformData), &m_uniformData, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();

		GLuint blockIndex = resourceManager.get<Resources::ShaderProgram>("BasicShader")->getUniformBlockIndex("u_camera_data");

		GLuint bindingPoint = 1;
		resourceManager.get<Resources::ShaderProgram>("BasicShader")->bindUniformBlock("u_camera_data", bindingPoint);
		glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_UBO);
	}

	void Camera::updateCameraUniform()
	{
		

		m_uniformData.viewMatrix = glm::inverse(transform.getMatrix());
		m_uniformData.projectionMatrix = getProjectionMatrix();

		
	}
}
}
