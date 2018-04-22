#pragma once
#include <SFML\System.hpp>
#include "../DamageTaker.h"

class GameManager;

class EnemyObject
{
public:
	EnemyObject(GameManager &aGameManager, DamageTaker &aDamageTaker, sf::Vector2f &aWorldCoords, float aHitRadius, float aMass, float aHeight);
	~EnemyObject();

	//Returns true if enemy died
	bool Damage(float aDamage, sf::Vector3f aImpactPoint, sf::Vector3f aVelocity) { return mDamageTaker.TakeDamage(aDamage, aImpactPoint, aVelocity); };
	float EvalDamage(float aDamage, sf::Vector3f aImpactPoint) { return mDamageTaker.EvaluateDamage(aDamage, aImpactPoint); }
	bool isDead() { return mDamageTaker.isDead(); }

	float DistanceTo(sf::Vector2f aWorldCoords);
	float DistanceSquaredTo(sf::Vector2f aWorldCoords);

	sf::Vector2f GetWorldCoords() { return mWorldCoords; }
	float GetMass() { return mMass; }
	float GetHitRadiusSquared() { return mHitRadius2; }
	float GetHeight(){ return mHeight; }

	void ForceMove(sf::Vector2f aDisplacement) { mWorldCoords += aDisplacement; }

private:
	GameManager &mGameManager;
	DamageTaker &mDamageTaker;

	sf::Vector2f &mWorldCoords;
	float mHitRadius2;
	float mMass;
	float mHeight;
};

