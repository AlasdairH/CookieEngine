#pragma once

// cstdlib

// external libs

// program

namespace CookieEng
{
namespace ResMgmt
{
	template <typename T>
	class Resource
	{
		virtual void load() = 0;
		virtual void unload() = 0;

		virtual bool isLoaded() = 0;
	};
}
}