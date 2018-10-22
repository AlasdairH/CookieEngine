#pragma once

// cstdlib

// external libs

// program
#include "CookieCore.h"

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
		/** @brief Called on component initialisation
		*
		*	Called before start, this method is called when the component is first created by the engine (usually on entity creation)
		*/
		void onInit() override;
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

	};

}