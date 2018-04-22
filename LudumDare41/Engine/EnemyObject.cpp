#include <math.h>

#include "GameManager.h"
#include "EnemyObject.h"



EnemyObject::EnemyObject(GameManager &aGameManager, DamageTaker &aDamageTaker, sf::Vector2f &aWorldCoords, float aHitRadius, float aMass, float aHeight) :
	mGameManager(aGameManager),
	mDamageTaker(aDamageTaker),
	mWorldCoords(aWorldCoords),
	mHitRadius2(aHitRadius * aHitRadius),
	mMass(aMass),
	mHeight(aHeight)
{
	aGameManager.GetEnemyManager().Add(*this);
}

EnemyObject::~EnemyObject()
{
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
