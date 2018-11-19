#pragma once

// cstdlib
#include <vector>
#include <memory>
#include <bitset>

// external libs
#include "GLM/gtx/common.hpp"

// program
#include "Macro.h"
#include "Component.h"

namespace CookieEng
{
namespace ECS
{
	class Component;

	/*! @class Entity
	*	@brief Holds together a group of components that are unique of each other
	*
	*	Holds a group of components that dictate the behaviour of the entity. Each component holds a pointer to its parent entity.
	*/
	class Entity
	{
	public:
		Entity();

		/** @brief Adds a component to the entity
		*	@param T The component type to add (must inherit from Component)
		*
		*	Takes a templated input of the component type to add (must inherit from Component) and adds it to the entity.
		*	It is at this point the components onInit method is run.
		*/
		template <typename T> 
		std::shared_ptr<T> addComponent()
		{
			if (hasComponent<T>())
			{
				return getComponent<T>();
			}

			std::shared_ptr<T> rtn = std::make_shared<T>();
			rtn->parent = this; 
			m_components.push_back(rtn);
			m_componentKey[getComponentTypeID<T>()] = true;
			rtn->onInit();

			return rtn;
		}

		/** @brief Gets a component from the Entity
		*	@param T The component type to get (must inherit from Component)
		*
		*	Takes a templated input of the component type to get (must inherit from Component) and returns a shared pointer to it.
		*	If the component is not found on the entity then it will add it and return the new component
		*/
		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			if (!hasComponent<T>())
			{
				addComponent<T>();
			}

			for (unsigned int i = 0; i < m_components.size(); ++i)
			{
				// attempty to cast the component at i to the requested component type
				std::shared_ptr<T> component = std::dynamic_pointer_cast<T>(m_components.at(i));

				// if the component casts to specified type
				if (component)
				{
					// return it!
					return component;
				}
			}

			// if the component isn't found, add it to the entity and return it
			return addComponent<T>();
		}

		/** @brief Tests to see if an Entity contains a component of type T
		*	@param T The component type to test (must inherit from Component)
		*
		*	Looks at the components on the Entity and returns wether the entity contains that component
		*/
		template <typename T>
		bool hasComponent()
		{
			if (m_componentKey[getComponentTypeID<T>()])
			{
				return true;
			}
			return false;

			/*
			// TODO: bitset implementation
			for (unsigned int i = 0; i < m_components.size(); i++)
			{
				// attempty to cast the component at i to the requested component type
				std::shared_ptr<T> component = std::dynamic_pointer_cast<T>(m_components.at(i));

				// if the component casts to specified type
				if (component)
				{
					return true;
				}
			}

			return false;
			*/
		}

		/** @brief Gets a unique integar
		*	@return An increasing integar that is used for assignment to a component type
		*
		*	Returns a new unique integar
		*/
		inline int getComponentTypeID()
		{
			static int componentID = -1;
			return ++componentID;
		}

		/** @brief Returns the corresonding unique integar for a specified type
		*	@return The unique integar
		*
		*	Takes in a component type and returns a unique integar for that type. Used by the bitset to get an index for the bit that represents the component.
		*/
		template <typename T>
		inline int getComponentTypeID()
		{
			static int typeID = getComponentTypeID();
			return typeID;
		}

		/** @brief Starts the underlying components
		*
		*	Loops through the linked components and starts them all
		*/
		void onStart()
		{
			for (std::vector<std::shared_ptr<Component> >::iterator it = m_components.begin(); it != m_components.end(); it++)
			{
				(*it)->onStart();
			}
		}

		/** @brief Updates the underlying components
		*
		*	Loops through the linked components and updates them all
		*/
		void onUpdate()
		{
			for (std::vector<std::shared_ptr<Component> >::iterator it = m_components.begin(); it != m_components.end(); it++)
			{
				(*it)->onUpdate();
			}
		}

		/** @brief Resets the parents of the entities on this component to be this entity
		*
		*	Loops through all the components on an entity and resets the parent pointer. This is required as sometimes the entity may move. I should have fuixed this through
		*	reserving more space in the entity vector but i'll keep this method just in case.
		*/
		void resetComponentParents()
		{
			for (std::vector<std::shared_ptr<Component> >::iterator it = m_components.begin(); it != m_components.end(); it++)
			{
				(*it)->parent = this;
			}
		}

	protected:
		std::vector<std::shared_ptr<Component>> m_components;	/**< The vector of components on the Entity */
		std::bitset<CNG_MAX_COMPONENTS> m_componentKey;			/**< A bitset representing the current components used to quickly test wether an entity has a certain component */

	};
}
}
