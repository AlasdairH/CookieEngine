#include <iostream>
#include "CookieEng.h"


#undef main

int main()
{
	CookieEng::Base Engine;
	Engine.initialise();

	CookieEng::ResMgmt::ResourceManager &resourceManager = CookieEng::ResMgmt::ResourceManager::getInstance();


	return 0;
}
