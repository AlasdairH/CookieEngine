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
		m_action();
	}

	void UIButton::setAction(std::function<void()> _func)
	{
		m_action = _func;
	}
}
}
}