#pragma once

// cstdlib
#include <vector>
#include <map>
#include <memory>

// external libs

// program
#include "Macro.h"
#include "Camera.h"
#include "Renderer.h"

#include "Entity.h"

#include "ResourceManager.h"

namespace CookieEng
{
namespace Scene
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void onUpdate();
		void draw();

	protected:
		int m_width = 1280;
		int m_height = 720;

		std::vector<ECS::Entity> m_entities;
		std::map<std::string, ECS::Entity> m_entityMap;

		std::shared_ptr<Object::Camera> m_camera;

		Graphics::Renderer m_renderer;
		std::shared_ptr<Graphics::FrameBuffer> m_frameBuffer;
	};
}
}