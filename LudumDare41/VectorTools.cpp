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

sf::Vector3f VectorTools::GetRandomScatter(float scatterval)
{
	sf::Vector3f scatter;
	scatter.x = -scatterval + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * scatterval)));
	scatter.y = -scatterval + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * scatterval)));
	scatter.z = -scatterval + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * scatterval)));
	return scatter;
}
