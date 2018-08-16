#include "Vertex.h"

namespace CookieEng
{
namespace Data
{

	bool Vertex::operator==(const Vertex &_other)
	{
		if (position == _other.position && textureCoordinate == _other.textureCoordinate && normal == _other.normal)
		{
			return true;
		}
		return false;
	}

}
}