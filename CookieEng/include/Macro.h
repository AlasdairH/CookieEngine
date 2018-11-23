#pragma once

#include <iostream>
#include <ctime>

#define DEBUG
//#define TEST
//#define RELEASE

#define _CRT_SECURE_NO_WARNINGS

#define USE_SDL
#define OPENGL
//#define D3D

// Ease of use macros for Application use
#define CNG_ACTIVE_SCENE CookieEng::Scene::Scene::activeScene
#define CNG_ACTIVE_CAMERA CookieEng::Object::Camera::activeCamera
#define CNG_DELTA_TIME CookieEng::Utilities::Times::deltaTime
#define CNG_SYS_TIME //*std::localtime(std::addressof(std::time(NULL)))

#define CNG_MIN(x, y) ((x) < (y) ? (x) : (y))
#define CNG_MAX(x, y) ((x) > (y) ? (x) : (y))

// the UniformBlock bindpoint for the camera View/Projection Matrix
#define CNG_GL_BINDPOINT_CAMERA_VP 1

// settings
// max entities per scene
#define CNG_MAX_ENTITIES 10000
// max conponents per entity
#define CNG_MAX_COMPONENTS 32
// wireframe
//#define CNG_DEBUG_RENDER_WIREFRAME


#ifdef DEBUG
	#define LOG_MESSAGE(_text) std::cout << "MESSAGE: " << _text << std::endl
	#define LOG_WARNING(_text) std::cout << "WARNING: " << _text << std::endl
	#define LOG_ERROR(_text) std::cout << "ERROR: " << _text << std::endl
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
