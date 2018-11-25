#pragma once

// cstdlib
#include <functional>

// external libs

// program
#include "Macro.h"
#include "Component.h"

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
		
	protected:
		
	};
}
}
}