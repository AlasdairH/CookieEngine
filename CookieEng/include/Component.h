#pragma once

// cstdlib


// external libs

// program
#include "Entity.h"

// TODO: Doxygen


namespace CookieEng
{
namespace ECS
{
	class Entity;

	class Component
	{
	public:
		Entity *parent;

		virtual void onInit() { }
		virtual void onStart() { }
		virtual void onUpdate() { }

	protected:

	};
}
}