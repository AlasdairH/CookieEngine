#pragma once

#include <iostream>
#include <chrono>

#define DEBUG
//#define TEST
//#define RELEASE

#define OPENGL
//#define D3D

#define CNG_ACTIVE_SCENE CookieEng::Scene::Scene::activeScene
#define CNG_ACTIVE_CAMERA CookieEng::Object::Camera::activeCamera
#define CNG_DELTA_TIME Utilities::Times::deltaTime
#define CNG_SYS_TIME std::chrono::system_clock::now()

#ifdef DEBUG
	#define LOG_MESSAGE(_text) std::cout << __TIME__ << " MESSAGE: " << _text << std::endl
	#define LOG_WARNING(_text) std::cout << __TIME__ << " WARNING: " << _text << std::endl
	#define LOG_ERROR(_text) std::cout << __TIME__ << " ERROR: " << _text << std::endl
#endif

#ifdef TEST
	#define LOG_MESSAGE(text)
	#define LOG_WARNING(text) std::cout << "WARNING: " << text << std::endl
	#define LOG_ERROR(text) std::cout << "ERROR: " << text << std::endl
#endif

#ifdef RELEASE
	#define LOG_MESSAGE(text)
	#define LOG_WARNING(text)
	#define LOG_ERROR(text) std::cout << "ERROR: " << text << std::endl
#endif
