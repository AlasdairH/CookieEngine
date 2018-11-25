#pragma once

// cstdlib
#include <functional>

// external libs

// program
#include "Entity.h"
#include "Macro.h"
#include "Transform.h"

namespace CookieEng
{
namespace Components
{
namespace GUI
{
	/*! @class UIElement
	*	@brief The base class for GUI elements
	*
	*	A base class that all GUI elements inherit from
	*/
	class UIElement : public ECS::Component
	{
	public:
		/** @brief Called when the mouse clicks the element
		*
		*	Called on mouse click of the GUI element
		*/
		virtual void onMouseClick() { };

		/** @brief Set the button width
		*	@param _width The button width in pixels
		*
		*	Sets the button width in pixels
		*/
		void setWidth(int _width);
		/** @brief Set the button height
		*	@param _height The button width in pixels
		*
		*	Sets the button height in pixels
		*/
		void setHeight(int _height);
		/** @brief Set the button position
		*	@param _position The x and y position in pixels
		*
		*	Sets the button position in pixels
		*/
		void setPosition(glm::vec2 _position);
		
	protected:
		
	};
}
}
}