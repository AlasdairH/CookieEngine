#include <iostream>

#include "CookieCore.h"


#undef main

int main()
{
	CookieEng::CookieCore engine;
	engine.initialise();

	CookieEng::ResMgmt::ResourceManager &resourceManager = CookieEng::ResMgmt::ResourceManager::getInstance();

	engine.start();


	return 0;
}
