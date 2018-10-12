#pragma once

// cstdlib

// external libs

// program
#include "ECS.h"

namespace CookieEng
{
namespace Core
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void update();
		void draw();

	protected:
		//ECS::Manager ecsManager;
	};
}
}