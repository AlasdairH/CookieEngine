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

		virtual void onStart() = 0;
		virtual void onUpdate() = 0;

	protected:

	};
}
};
