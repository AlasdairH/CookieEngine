#pragma once

// cstdlib
#include <stdint.h>

// external libs

// program


namespace CookieEng
{
namespace Utilities
{
	/*! @class Times
	*	@brief Holds engine time values
	*
	*	Frame and engine timing such as Delta Time are stored in this for use all over the engine. This is usefull for frame independent movement etc.
	*/
	struct Times
	{
	public:
		static double deltaTime;	/**< The time in seconds it took to complete the last frame */
	};
}
}