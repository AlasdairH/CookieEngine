#pragma once

// cstdlib

// external libs

// program
#include "CookieCore.h"

//TODO: Doxygen

namespace Crumble
{
	/*! @class GameController
	*	@brief
	*
	*
	*/
	class Player : public CookieEng::ECS::Component
	{
	public:
		/** @brief Called on component initlaisation
		*
		*	Called first before start, this method is called when the engine first adds the object
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