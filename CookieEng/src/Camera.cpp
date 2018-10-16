#include "Camera.h"

namespace CookieEng
{
namespace Object
{
	Camera::Camera()
	{
		m_fov = 0.7f;
		m_aspect = 1.0f;

		// create the uniform buffer
		m_uniformBuffer = std::make_unique<Graphics::VertexBuffer>(Graphics::CNG_UNIFORM_BUFFER);
		// load the data to the uniform buffer
		m_uniformBuffer->loadData(&m_uniformData, 0, sizeof(m_uniformData));

		//glGenBuffers(1, &m_UBO);
		//glBindBuffer(GL_UNIFORM_BUFFER, m_UBO);
		//glBufferData(GL_UNIFORM_BUFFER, sizeof(m_uniformData), &m_uniformData, GL_DYNAMIC_DRAW);
		//glBindBuffer(GL_UNIFORM_BUFFER, 0);

		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();

		// set the binding point
		GLuint bindingPoint = 1;
		// link the BasicShader Uniform block "u_camera_data" to the binding point
		resourceManager.get<Resources::ShaderProgram>("BasicShader")->linkUniformBlock("u_camera_data", bindingPoint);
		// link the uniform buffer to the binding point
		m_uniformBuffer->bindBase(bindingPoint);
		// now the shader and the uniform buffer are pointing at the same binding point the fun can commence
	}

	void Camera::updateCameraUniform()
	{
		// grab the new matrices
		m_uniformData.viewMatrix = glm::inverse(transform.getMatrix());
		m_uniformData.projectionMatrix = getProjectionMatrix();

		// bind the uniform buffer
		m_uniformBuffer->bind();
		// load the data to the uniform buffer
		m_uniformBuffer->loadData(&m_uniformData, 0, sizeof(m_uniformData));
	}
}
}
