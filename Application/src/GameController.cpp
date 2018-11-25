#include "GameController.h"

namespace Crumble
{
	void GameController::onStart()
	{
		CookieEng::ECS::Entity player;
		player.addComponent<CookieEng::Components::Transform>();
		player.addComponent<CookieEng::Components::Renderable>();
		player.addComponent<Crumble::Player>();

		// add and set bounding box
		
		player.addComponent<CookieEng::Components::BoundingBox>();
		auto boundingBox = player.getComponent<CookieEng::Components::BoundingBox>();
		boundingBox->pullFromMesh();
		
		m_player = CNG_ACTIVE_SCENE->addEntity(player);

		m_audioSource.assign("DunkSound");
	}

	void GameController::onUpdate()
	{
		CookieEng::Input::InputManager &inputManager = CookieEng::Input::InputManager::getInstance();
		CookieEng::ResMgmt::ResourceManager &resourceManager = CookieEng::ResMgmt::ResourceManager::getInstance();
		std::shared_ptr<CookieEng::Input::Keyboard::Keyboard> keyboard = inputManager.getKeyboard();

		if (m_missed >= 10)
		{
			m_isPlaying = false;
		}

		if (m_isPlaying)
		{
			// check if a new cookie is to be spawned
			float test = CookieEng::Utilities::UtilsFloat::randFloat(0.0f, 1.0f);
			if (test > 0.99f)
			{
				// get a random x pos over the top of the screen
				int xpos = (int)(CookieEng::Utilities::UtilsFloat::randFloat(-8.0f, 8.0f) / 2) * 2;
				CookieEng::ECS::Entity object;
				object.addComponent<CookieEng::Components::Transform>();
				object.getComponent<CookieEng::Components::Transform>()->setPosition(glm::vec3(xpos, 5, 0));
				object.addComponent<CookieEng::Components::Renderable>();
				auto rednerable = object.getComponent<CookieEng::Components::Renderable>();
				object.addComponent<CookieEng::Components::BoundingBox>();

				object.addComponent<Crumble::Collectable>();

				auto boundingBox = object.getComponent<CookieEng::Components::BoundingBox>();
				boundingBox->pullFromMesh();

				m_collectables.emplace_back(CNG_ACTIVE_SCENE->addEntity(object));
			}
		}


		std::vector<unsigned int> indexToRemove;

		for (unsigned int i = 0; i < m_collectables.size(); ++i)
		{
			if (m_collectables[i].expired())
			{
				indexToRemove.push_back(i);
				continue;
			}

			// if the collectable has gone over the bottom of the screen
			if (m_collectables[i].lock()->getComponent<CookieEng::Components::Transform>()->getPositionVec3().y < -6.0f)
			{
				CNG_ACTIVE_SCENE->removeEntity(m_collectables[i].lock());
				indexToRemove.push_back(i);

				++m_missed;
				LOG_MESSAGE("Missed: " << m_missed);
				
				if (m_missed >= 5)
				{
					// create the win label
					CookieEng::ECS::Entity uiLoss;
					uiLoss.addComponent<CookieEng::Components::Transform>();
					uiLoss.addComponent<CookieEng::Components::GUI::UIButton>();
					auto button = uiLoss.getComponent<CookieEng::Components::GUI::UIButton>();
					button->setWidth(150);
					button->setHeight(100);
					button->setPosition(glm::vec2((CNG_ACTIVE_CAMERA->getViewportWidth() / 2) - (button->getWidth() / 2), (CNG_ACTIVE_CAMERA->getViewportHeight() / 2) - (button->getHeight() / 2)));
					button->setMaterial(resourceManager.get<CookieEng::Resources::Material>("WinLabelMaterial"));
					button->getMaterial()->setDiffuse("LostLabelTexture");
					CNG_ACTIVE_SCENE->addEntity(uiLoss);
				}
			}

			// test collision between cookie (Collectable) and mug (Player)
			if (m_collectables[i].lock()->getComponent<CookieEng::Components::BoundingBox>()->getBoundingBox().testCollision(m_player->getComponent<CookieEng::Components::BoundingBox>()->getBoundingBox()))
			{
				LOG_MESSAGE("Collision Detected");
				CNG_ACTIVE_SCENE->removeEntity(m_collectables[i].lock());
				indexToRemove.push_back(i);
				++m_score;
				LOG_MESSAGE("Score: " << m_score);
				// play dunk sound
				m_audioSource.play();

				if (m_score >= 10)
				{
					LOG_MESSAGE("WINNER!");

					// create the win label
					CookieEng::ECS::Entity uiWin;
					uiWin.addComponent<CookieEng::Components::Transform>();
					uiWin.addComponent<CookieEng::Components::GUI::UIButton>();
					auto button = uiWin.getComponent<CookieEng::Components::GUI::UIButton>();
					button->setWidth(150);
					button->setHeight(100);
					button->setPosition(glm::vec2((CNG_ACTIVE_CAMERA->getViewportWidth() / 2) - (button->getWidth() / 2), (CNG_ACTIVE_CAMERA->getViewportHeight() / 2) - (button->getHeight() / 2)));
					button->setMaterial(resourceManager.get<CookieEng::Resources::Material>("WinLabelMaterial"));
					CNG_ACTIVE_SCENE->addEntity(uiWin);

					// pause the game
					CNG_ACTIVE_SCENE->togglePause();
				}
			}
		}

		
		// sort the indices
		std::sort(indexToRemove.begin(), indexToRemove.end());
		// reverse to decend
		std::reverse(indexToRemove.begin(), indexToRemove.end());

		for (unsigned int i = 0; i < indexToRemove.size(); ++i)
		{
			m_collectables.erase(m_collectables.begin() + indexToRemove[i]);
		}
		
		indexToRemove.clear();
		auto transform = m_player->getComponent<CookieEng::Components::Transform>();
		
		if ((keyboard->isKeyDown(CookieEng::Input::Keyboard::CNG_KEY_A) && transform->getPositionVec3().x > -6))
		{
			transform->translate(glm::vec3(-6, 0, 0) * CNG_DELTA_TIME);
		}
		if ((keyboard->isKeyDown(CookieEng::Input::Keyboard::CNG_KEY_D) && transform->getPositionVec3().x < 6))
		{
			transform->translate(glm::vec3(6, 0, 0) * CNG_DELTA_TIME);
		}
		if ((keyboard->isKeyDown(CookieEng::Input::Keyboard::CNG_KEY_W)))
		{
			CNG_ACTIVE_CAMERA->transform.translate(glm::vec3(0, 0, -5) * CNG_DELTA_TIME);
		}
		if ((keyboard->isKeyDown(CookieEng::Input::Keyboard::CNG_KEY_S)))
		{
			CNG_ACTIVE_CAMERA->transform.translate(glm::vec3(0, 0, 5) * CNG_DELTA_TIME);
		}

		// if controller 0 is connected
		if (inputManager.validController(0))
		{
			transform->translate(glm::vec3(-6, 0, 0) * inputManager.getGamepad(0)->getAxis("leftx") *  CNG_DELTA_TIME * -1.0f);
			//LOG_MESSAGE(inputManager.getGamepad(0)->getAxis("leftx"));
		}
	}
}


