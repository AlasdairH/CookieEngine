#pragma once

// cstdlib

// external libs

// program

namespace CookieEng
{
namespace ECS
{
	class Entity;

	/*! @class Component
	*	@brief The component base class
	*
	*	The base class that all the components of entities must inherit from. Through polymorphism this
	*	class provides the virtual methods that can be overriden by components to allow for the correct
	*	usage.
	*/
	class Component
	{
	public:
		Entity *parent;

		/** @brief Called on component initialisation
		*
		*	Called before start, this method is called when the component is first created by the engine (usually on entity creation)
		*/
		virtual void onInit() { }
		/** @brief Called on component start
		*
		*	Called after onInit, this method is called when the engine runs through the first game loop
		*/
		virtual void onStart() { }
		/** @brief Called on component update
		*
		*	Called after start and on every frame
		*/
		virtual void onUpdate() { }

	protected:

	};
}
}