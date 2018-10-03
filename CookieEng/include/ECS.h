#pragma once

// cstdlib
#include <iostream>
#include <array>
#include <bitset>
#include <algorithm>

// external libs

// program
#include "Entity.h"
#include "Component.h"

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

		inline ComponentID getComponentTypeID()
		{
			static ComponentID lastID = 0;
			return ++lastID;
		}

		template<typename T> 
		inline ComponentID getComponentTypeID()
		{
			static ComponentID typeID = getComponentTypeID();
			return typeID;
		}

		using ComponentArray = std::array<Component *, MAX_COMPONENTS>;
		using ComponentBitSet = std::bitset<MAX_COMPONENTS>;

		// ----------------------------- COMPONENT -----------------------------
		class Component
		{
		public:
			Component() {};
			virtual ~Component() {};

			Entity *parentEntity;

			virtual void onStart() {};
			virtual void onUpdate() {};

		protected:

		};

		// ----------------------------- ENTITY -----------------------------
		class Entity
		{
		public:
			void start()
			{
				for (auto &c : m_components)
					c->onStart();

			}
			void update()
			{
				for (auto &c : m_components)
					c->onUpdate();
			}

			inline bool isActive() { return m_active; }
			inline void destroy() { m_active = false; }

			template<typename T, typename... TArgs>
			T& addComponent(TArgs&&... _args)
			{
				T* c(new T(std::forward<TArgs>(_args)...));
				c->parentEntity = this;
				std::unique_ptr<Component> uPtr{ c };
				m_components.emplace_back(std::move(uPtr));

				m_componentArray[getComponentTypeID<T>()] = c;
				m_componentBitset[getComponentTypeID<T>()] = true;

				c->onStart();
				return *c;
			}

			template<typename T>
			T& getComponent()
			{
				auto ptr(m_componentArray[getComponentTypeID<T>()]);
				return *static_cast<T*>(ptr);
			}

			template<typename T>
			bool hasComponent() const
			{
				return m_componentBitset[getComponentTypeID<T>];
			}

		protected:
			bool m_active;
			std::vector<std::unique_ptr<Component>> m_components;

			ComponentArray m_componentArray;
			ComponentBitSet m_componentBitset;
		};

		// ----------------------------- MANAGER -----------------------------
		class Manager
		{
		public:

			Entity &addEntity()
			{
				Entity *e = new Entity;
				std::unique_ptr<Entity> uPtr{ e };
				m_entities.emplace_back(std::move(uPtr));
				return *e;
			}

			void update()
			{
				for (auto &e : m_entities)
					e->update();
			}
			
			void refresh()
			{
				m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities), [](const std::unique_ptr<Entity> &entity) 
				{
					return !entity->isActive();
				}
				), std::end(m_entities));
			}

		protected:
			std::vector<std::unique_ptr<Entity>> m_entities;
		};
	}
}
