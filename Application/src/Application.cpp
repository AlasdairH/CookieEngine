#include <iostream>
#include "CookieEng.h"


#undef main

int main()
{
	std::cout << "Hello World" << std::endl;

	CookieEng::Base Engine;
	Engine.start();

	system("pause");
	return 0;
}
