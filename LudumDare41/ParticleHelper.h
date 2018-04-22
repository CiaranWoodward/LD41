#pragma once
#include "SFML\System.hpp"

class ParticleHelper
{
public:
	ParticleHelper(sf::Vector3f aStartPos, sf::Vector3f aStartVelocity, float aBounceFactor, float aFrictionFactor, float aAirResFactor);
	~ParticleHelper();

	sf::Vector3f GetNewCoords(sf::Time dt);

	sf::Vector3f GetCoords() { return mCoords; }
	sf::Vector3f GetVelocity() { return mVelocity; }
	bool IsDead() { return mDead; }

	void vertBounce() { mVelocity.y = mVelocity.y * -mBounceFactor; mVelocity.x = mVelocity.x * -mBounceFactor; }

private:
	sf::Vector3f mCoords;
	sf::Vector3f mVelocity;
	
	float mBounceFactor;
	float mFrictionFactor;
	float mAirResFactor;

	bool mDead;

	static const float kGravity;
};
