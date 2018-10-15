#pragma once

// cstdlib
#include <vector>
#include <memory>

// external libs

// program
#include "Macro.h"
#include "Component.h"

// TODO: Doxygen

#define ADDCOMPONENT \
  std::shared_ptr<T> rtn = std::make_shared<T>(); \
  rtn->parent = this; \
  m_components.push_back(rtn);


namespace CookieEng
{
namespace ECS
{
	class Component;

	class Entity
	{
	public:
		Entity();

		template <typename T> 
		std::shared_ptr<T> addComponent()
		{
			if (hasComponent<T>())
			{
				return getComponent<T>();
			}

			ADDCOMPONENT
			rtn->onInit();

			return rtn;
		}

		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				// attempty to cast the component at i to the requested component type
				std::shared_ptr<T> component = std::dynamic_pointer_cast<T>(m_components.at(i));

				// if the component casts to specified type
				if (component)
				{
					return component;
				}
			}

			LOG_ERROR("Component not found");
		}

		template <typename T>
		bool hasComponent()
		{
			// TODO: bitset implementation
			for (size_t i = 0; i < m_components.size(); i++)
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
		}

	protected:
		std::vector<std::shared_ptr<Component>> m_components;
	};
}
}
