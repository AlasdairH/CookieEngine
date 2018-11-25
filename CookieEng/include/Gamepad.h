#pragma once

// cstdlib

// external libs
#include "SDL/SDL.h"

// program
#include "Macro.h"

namespace CookieEng
{
namespace Input
{
namespace Controllers
{
	// righttrigger
	// lefttrigger
	// leftx
	// lefty
	// rightx
	// righty


	/*! @class Gamepad
	*	@brief A Gamepad class that handles the state of a gamepad or joystick
	*
	*	This Gamepad class contains the data for buttons and axis on a joystick.
	*/
	class Gamepad
	{
	public:
		/** @brief Joystick Ctor
		*
		*	Does nothing
		*/
		Gamepad();


		/** @brief Updates the controller
		*
		*	Updates the controller axis
		*/
		void update();

		/** @brief Assigns the controller to an SDL input
		*	@param _index The controller to asign to the abstraction
		*
		*	Assigns the controller to an SDL Contorller input
		*/
		void assign(int _index);

		/** @brief Gets the axis value
		*	@param _axis The axis to get the value from
		*
		*	Gets the value of an axis
		*/
		float getAxis(std::string _axis);

	protected:
		SDL_GameController		*m_gameController;	/**< The Game Controller */
		SDL_Joystick			*m_joystick;		/**< The Joystick */
	};
}
}
}
