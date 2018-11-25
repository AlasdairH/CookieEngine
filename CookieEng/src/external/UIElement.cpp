#include "UIElement.h"

namespace CookieEng
{
namespace Components
{
namespace GUI
{
	void UIElement::setWidth(int _width)
	{
		auto transform = parent->getComponent<CookieEng::Components::Transform>();
		transform->setScale(glm::vec3((float)_width, transform->getScaleVec3().y, 1));
	}
	void UIElement::setHeight(int _height)
	{
		auto transform = parent->getComponent<CookieEng::Components::Transform>();
		transform->setScale(glm::vec3(transform->getScaleVec3().x, (float)_height, 1));
	}
	void UIElement::setPosition(glm::vec2 _position)
	{
		auto transform = parent->getComponent<CookieEng::Components::Transform>();
		transform->setPosition(glm::vec3(_position.x, _position.y, 0));
	}
}
}
}