#pragma once

// cstdlib
#include <functional>
#include <vector>
#include <memory>

// external libs
#include "GLM/common.hpp"

// program
#include "Macro.h"
#include "UIElement.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"

namespace CookieEng
{
namespace Components
{
namespace GUI
{
	/*! @class UIButton
	*	@brief A button UI element
	*
	*	A button component which
	*/
	class UIButton : public UIElement
	{
	public:
		/** @brief Called on button initialisation
		*
		*	Called on button initialisation in order to create the vertex array
		*/
		void onInit() override;	

		/** @brief Called when the mouse clicks the button
		*
		*	Called on mouse click of the button
		*/
		void onMouseClick() override;

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

		/** @brief Returns the VAO
		*	@return A renderable VAO
		*
		*	Returns a VAO which can be used by a renderer to render the material
		*/
		inline std::shared_ptr<Graphics::VertexArray> getVAO() { return m_mesh->getVAO(); }
		/** @brief Returns the IBO
		*	@return An IBO indexing the member VBO
		*
		*	Return the IBO which indexes the objects VBO
		*/
		inline std::shared_ptr<Graphics::VertexBuffer> getIBO() { return m_mesh->getIBO(); }
		/** @brief Returns the Material
		*	@return The material used to render the GUI
		*
		*	Returns the material used to render the GUI
		*/
		inline std::shared_ptr<Resources::Material> getMaterial() { return m_material; }

	protected:
		std::function<void(void*)>					m_action = [](void* data) { };		/**< Function pointer to the action to perform on button click */

		std::shared_ptr<Resources::Material>		m_material;							/**< The material used for rendering the button */
		std::shared_ptr<Resources::Mesh>			m_mesh;								/**< The mesh to render the GUI on */
	};
}
}
}