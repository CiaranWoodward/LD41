#pragma once
#include "SFML\System\Vector2.hpp"
#include "SFML\System\Vector3.hpp"

class VectorTools
{
public:
	VectorTools();
	~VectorTools();

	//All normalize functions modify the passed vector and return the magnitude
	static float Normalize(sf::Vector2f &vec);
};

