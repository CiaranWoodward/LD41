#pragma once
#include "SFML\System\Vector3.hpp"

class DamageTaker
{
public:
	DamageTaker() {}
	virtual ~DamageTaker() {}

	virtual float EvaluateDamage(float aDamage, sf::Vector3f aImpactPoint) = 0;
	virtual bool TakeDamage(float aDamage, sf::Vector3f aImpactPoint, sf::Vector3f aVelocity) = 0;
	virtual bool isDead() = 0;
};

