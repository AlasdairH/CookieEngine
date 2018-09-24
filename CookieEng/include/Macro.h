#pragma once

#include <iostream>

#define DEBUG

//#define TEST
//#define RELEASE

#define OPENGL
//#define D3D

#ifdef DEBUG
	#define LOG_MESSAGE(text) std::cout << "MESSAGE: " << text << std::endl
	#define LOG_WARNING(text) std::cout << "WARNING: " << text << std::endl
	#define LOG_ERROR(text) std::cout << "ERROR: " << text << std::endl
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
