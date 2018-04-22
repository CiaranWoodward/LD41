#include "VectorTools.h"
#include <cmath>


VectorTools::VectorTools()
{
}


VectorTools::~VectorTools()
{
}

float VectorTools::Normalize(sf::Vector2f & vec)
{
	float mag = std::sqrtf(vec.x * vec.x + vec.y * vec.y);
	if (mag != 0)
		vec /= mag;
	return mag;
}

float VectorTools::Normalize(sf::Vector3f & vec)
{
	float mag = std::sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (mag != 0)
		vec /= mag;
	return mag;
}