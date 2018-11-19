#pragma once

// cstdlib

// external libs

// program
#include "CookieCore.h"
#include "Ray.h"
#include "BoundingBox.h"
#include "Collectable.h"
#include "Player.h"

namespace Crumble
{
	/*! @class GameController
	*	@brief 
	*
	*	
	*/
	class GameController : public CookieEng::ECS::Component
	{
	public:
		/** @brief Called on component start
		*
		*	Called after onInit, this method is called when the engine runs through the first game loop
		*/
		 void onStart() override;
		/** @brief Called on component update
		*
		*	Called after start and on every frame
		*/
		void onUpdate() override;

	protected:
		std::vector<std::shared_ptr<CookieEng::ECS::Entity>> m_collectables;
	};

}