#include <math.h>

#include "GameManager.h"
#include "EnemyObject.h"



EnemyObject::EnemyObject(GameManager &aGameManager, sf::Vector2f &aWorldCoords, float aHitRadius, float aMass) :
	mGameManager(aGameManager),
	mWorldCoords(aWorldCoords),
	mHitRadius2(aHitRadius * aHitRadius),
	mMass(aMass)
{
	aGameManager.GetEnemyManager().Add(*this);
}


EnemyObject::~EnemyObject()
{
}

bool EnemyObject::Damage(int32_t damage)
{
	return (false);
}

float EnemyObject::DistanceTo(sf::Vector2f aWorldCoords)
{
	return sqrtf(DistanceSquaredTo(aWorldCoords));
}

float EnemyObject::DistanceSquaredTo(sf::Vector2f aWorldCoords)
{
	sf::Vector2f delt = aWorldCoords - mWorldCoords;
	delt.y = delt.y * 2.f; //Double the Y to account for the dimetric projection

	return (delt.x * delt.x) + (delt.y * delt.y);
}
