#pragma once

// cstdlib

// external libs

// program
#include "ShaderProgram.h"

// TODO: Doxygen
// TODO: Finish

namespace CookieEng
{
namespace Core
{
	/*! @class Material
	*	@brief Abstracted OpenGL Program
	*
	*	Abstracts and provides simple utilities for an OpenGL Shader Program. The program MUST be verified before it can be bound.
	*/
	class Material
	{
	public:
		Material();
		~Material() {}

	protected:
		Graphics::ShaderProgram *m_shaderProgram;
	};
}
}