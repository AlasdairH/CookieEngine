#pragma once

// cstdlib

// external libs

// program
#include "Macro.h"

namespace CookieEng
{
namespace Components
{
	class Component
	{
	public:
		Component();
		~Component();

		virtual void onStart();
		virtual void onUpdate();

	protected:

	};
}
};
