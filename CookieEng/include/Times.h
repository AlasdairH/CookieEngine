#pragma once

// cstdlib
#include <iostream>
#include <cstdio>
#include <ctime>
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

	/*! @class Timer
	*	@brief A timer that can time from start to an abitrary point
	*
	*	A timer that is started on instantiation and can be polled for the current time since start at any point
	*/
	class Timer
	{
	public:
		/** @brief Timer Ctor
		*
		*	Starts the timer
		*/
		Timer() { m_start = std::clock(); }
		/** @brief Get the duration of the timer
		*	@return A float containing the current duration in seconds
		*
		*	Returns the time that has passed since the start of the timer in seconds
		*/
		float getDuration() { return (std::clock() - m_start) / (float)CLOCKS_PER_SEC; }

	protected:
		std::clock_t m_start;	/**< The start time of the timer */
	};
}
}