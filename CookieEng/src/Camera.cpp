#include "Camera.h"

namespace CookieEng
{
namespace Object
{
	Camera *Camera::activeCamera = nullptr;

	Camera::Camera()
	{
		m_fovRad = 0.7f;
		m_aspect = 1.0f;

		init();
	}

	Camera::Camera(const int _resolutionWidth, const int _resolutionHeight)
	{
		m_fovRad = 0.7f;
		setAspectRatio(_resolutionWidth / (float)_resolutionHeight);

		m_viewportWidth = _resolutionWidth;
		m_viewportHeight = _resolutionHeight;

		init();
	}

	void Camera::init()
	{
		// create the uniform buffer
		m_uniformBuffer = std::make_shared<Graphics::VertexBuffer>(Graphics::CNG_BUFFER_UNIFORM);
		// load the data to the uniform buffer
		m_uniformBuffer->loadData(&m_uniformData, 0, sizeof(m_uniformData));

		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();

		// link the uniform buffer to the binding point
		m_uniformBuffer->bindBase(CNG_GL_BINDPOINT_CAMERA_VP);
		// now the shader and the uniform buffer are pointing at the same binding point the fun can commence

		// if there is no current active camera, set it to this one
		if (Camera::activeCamera == nullptr)
		{
			activeCamera = this;
		}
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
