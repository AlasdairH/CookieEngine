#pragma once

// cstdlib
#include <functional>

// external libs

// program
#include "Entity.h"
#include "Macro.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"

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

		/** @brief Gets the element width
		*	@return The width of the element
		*
		*	Takes the width scale from the parents transform component
		*/
		inline float getWidth() { return parent->getComponent<CookieEng::Components::Transform>()->getScaleVec3().x; }
		/** @brief Gets the element height
		*	@return The height of the element
		*
		*	Takes the height scale from the parents transform component
		*/
		inline float getHeight() { return parent->getComponent<CookieEng::Components::Transform>()->getScaleVec3().y; }

		/** @brief Set the Material
		*	@param _material The Material to use on the UI Element
		*
		*	Sets the material of the UI element
		*/
		inline void setMaterial(std::shared_ptr<Resources::Material> _material) { m_material = _material; }
		
	protected:
		std::shared_ptr<Resources::Material>		m_material;					/**< The material used for rendering the button */
		std::shared_ptr<Resources::Mesh>			m_mesh;						/**< The mesh to render the GUI on */
	};
}
}
}