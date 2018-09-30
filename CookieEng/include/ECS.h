#pragma once

// cstdlib
#include <iostream>

// external libs

// program

// TODO: Doxygen


namespace CookieEng
{
	namespace ECS
	{
		// forward delcare entity and component
		class Entity;
		class Component;

		constexpr std::size_t MAX_COMPONENTS = 32;

		using ComponentID = std::size_t;

		inline ComponentID getComponentID()
		{
			static ComponentID lastID = 0;
			return ++lastID;
		}

		template<typename T> 
		inline ComponentID getComponentID()
		{
			static ComponentID typeID = getComponentID();
			return typeID;
		}
	}
}
