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
	class Scene : public std::enable_shared_from_this<Scene>
	{
	public:
		Scene();
		~Scene();

		inline void setActive() { activeScene = this; }

		void addEntity(const ECS::Entity &_entity);

		void onUpdate();
		void draw();

		static Scene *activeScene;	/**< The currently active camera */

	protected:
		int m_width = 1280;
		int m_height = 720;

		std::vector<ECS::Entity> m_entities;
		std::map<std::string, ECS::Entity> m_entityMap;

		Graphics::Renderer m_renderer;
		std::shared_ptr<Graphics::FrameBuffer> m_frameBuffer;
	};
}
}