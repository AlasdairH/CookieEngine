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
	/*! @class Scene
	*	@brief A level representation containing entities
	*
	*	The scene class handles the entities within it, grouping a level into one place. The activeScene static points to the currently
	*	active scene. On creation of a scene, if no active scene is set then it is set to that scene.
	*/
	class Scene : public std::enable_shared_from_this<Scene>
	{
	public:
		/** @brief Scene Ctor
		*
		*	Initialises the scene. This sets up the framebuffer and reserves the memory for entities.
		*/
		Scene();
		/** @brief Scene Dtor
		*
		*	Does nothing
		*/
		~Scene();

		/** @brief Sets the active scene to this scene
		*
		*	This sets the engine's active scene to this one. The engine will perform the programs requested actions and render the active scene.
		*/
		inline void setActive() { activeScene = this; }

		/** @brief Gets UI elements from screen position
		*	@param the position on the screen in pixels to check under
		*
		*	Looks for any UI element under the screen position and returns it
		*/
		std::shared_ptr<ECS::Entity> getUIUnderScreenPosition(glm::vec2 _screenPosition);

		/** @brief Adds an entity to the scene
		*	@return A shared pointer to the newly added entity
		*	@param _entity The entity to add
		*
		*	Adds an entity to the scene. This will instantiate it.
		*/
		std::shared_ptr<ECS::Entity> addEntity(ECS::Entity &_entity);
		/** @brief Adds an entity to the scene
		*	@return A shared pointer to the entity requested by index
		*	@param _index The index of the entity to get.
		*
		*	Gets en entity by index. This is pretty useless most of the time as you usually have no idea what you're going to get back.
		*/
		std::shared_ptr<ECS::Entity> getEntity(const int _index);

		/** @brief Removes an entity from the scene
		*	@param _entity The entity to remove
		*
		*	This method will not actually remove an entity. This will simply mark the entity for removal, to actually remove it the clean() method must be run.
		*	To avoid issues, do not run a clean between an update and draw, preferably do it before or after both.
		*/
		void removeEntity(std::shared_ptr<ECS::Entity> _entity);

		/** @brief Starts the scene
		*
		*	Starts the scene. This loops through all the entities and runs their start method.
		*/
		void onStart();  
		/** @brief Updates the scene
		*
		*	Updates the scene. This updates all the entities and their respective components.
		*/
		void onUpdate();
		/** @brief Draws the scene
		*
		*	Uses the member renderer to render the scene to a framebuffer and then render that to the screen.
		*/
		void draw();
		/** @brief Cleans the scene
		*
		*	Clean will remove any entities that are marked for deletion.
		*/
		void clean();

		static Scene *activeScene;	/**< The currently active scene */

	protected:
		int											m_width;		/**< The width of the scene's resolution */
		int											m_height;		/**< The height of the scene's resolution */

		std::vector<std::shared_ptr<ECS::Entity>>	m_entities;		/**< The vector of entities in the scene */
		std::vector<std::weak_ptr<ECS::Entity>>		m_uiEntities;	/**< The vector of entities in the scene that contain UI elements */
		std::vector<int>							m_deleteQueue;	/**< Stores the indices of entities to be removed at the end of the update */
		std::map<std::string, ECS::Entity>			m_entityMap;	/**< Not used? */

		Graphics::Renderer							m_renderer;		/**< The renderer used in the draw method */
		std::shared_ptr<Graphics::FrameBuffer>		m_frameBuffer;	/**< The framebuffer that will be rendered to */
	};
}
}