#include "GameController.h"



namespace Crumble
{
	void GameController::onStart()
	{
		CookieEng::ECS::Entity player;
		player.addComponent<CookieEng::Components::Transform>();
		player.addComponent<CookieEng::Components::Renderable>();
		player.addComponent<Crumble::Player>();
		m_player = CNG_ACTIVE_SCENE->addEntity(player);
	}

	void GameController::onUpdate()
	{
		std::shared_ptr<CookieEng::Input::Keyboard::Keyboard> keyboard = CookieEng::Input::InputManager::getInstance().getKeyboard();

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
				int xpos = (int)(CookieEng::Utilities::UtilsFloat::randFloat(-8.0f, 8.0f) / 2) * 2;
				CookieEng::ECS::Entity object;
				object.addComponent<CookieEng::Components::Transform>();
				object.getComponent<CookieEng::Components::Transform>()->setPosition(glm::vec3(xpos, 5, 0));
				object.addComponent<CookieEng::Components::Renderable>();
				object.addComponent<Crumble::Collectable>();
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

			if (m_collectables[i].lock()->getComponent<CookieEng::Components::Transform>()->getPositionVec3().y < -5.0f)
			{
				CNG_ACTIVE_SCENE->removeEntity(m_collectables[i].lock());
				indexToRemove.push_back(i);

				++m_missed;
				LOG_MESSAGE("Missed: " << m_missed);
				continue;
			}

			// test collision between cookie (Collectable) and mug (Player)
			if (m_collectables[i].lock()->getComponent<CookieEng::Components::Renderable>()->getBoundingBox().testCollision(m_player->getComponent<CookieEng::Components::Renderable>()->getBoundingBox()))
			{
				LOG_MESSAGE("Collision Detected");
				CNG_ACTIVE_SCENE->removeEntity(m_collectables[i].lock());
				indexToRemove.push_back(i);
				++m_score;
				LOG_MESSAGE("Score: " << m_score);
			}
		}

		
		// sort the indices
		std::sort(indexToRemove.begin(), indexToRemove.end());
		// reverse to decend
		std::reverse(indexToRemove.begin(), indexToRemove.end());

		for (int i = 0; i < indexToRemove.size(); ++i)
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

		if (keyboard->isKeyDown(CookieEng::Input::Keyboard::CNG_KEY_W))
		{
			//CNG_ACTIVE_CAMERA->transform.translate(glm::vec3(0, 0, -10) * CookieEng::Utilities::Times::deltaTime);
		}
		if (keyboard->isKeyDown(CookieEng::Input::Keyboard::CNG_KEY_S))
		{
			//CNG_ACTIVE_CAMERA->transform.translate(glm::vec3(0, 0, 10) * CookieEng::Utilities::Times::deltaTime);
		}
	}
}


