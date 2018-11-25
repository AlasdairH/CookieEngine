#include "UIButton.h"

namespace CookieEng
{
namespace Components
{
namespace GUI
{
	void UIButton::onInit()
	{
		ResMgmt::ResourceManager &resourceManager = ResMgmt::ResourceManager::getInstance();
		m_mesh = resourceManager.get<Resources::Mesh>("GUIPlane");
		m_material = resourceManager.get<Resources::Material>("GUIMaterial");
	}

	void UIButton::onMouseClick()
	{

	}

	void UIButton::setWidth(int _width)
	{
		auto transform = parent->getComponent<CookieEng::Components::Transform>();
		transform->setScale(glm::vec3((float)_width, transform->getScaleVec3().y, 1));
	}
	void UIButton::setHeight(int _height)
	{
		auto transform = parent->getComponent<CookieEng::Components::Transform>();
		transform->setScale(glm::vec3(transform->getScaleVec3().x, (float)_height, 1));
	}
	void UIButton::setPosition(glm::vec2 _position)
	{
		auto transform = parent->getComponent<CookieEng::Components::Transform>();
		transform->setPosition(glm::vec3(_position.x, _position.y, 0));
	}
}
}
}