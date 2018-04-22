#pragma once
#include <SFML\System.hpp>

class GameManager;

class EnemyObject
{
public:
	EnemyObject(GameManager &aGameManager, sf::Vector2f &aWorldCoords, float aHitRadius, float aMass);
	~EnemyObject();

	//Returns true if enemy died
	bool Damage(int32_t damage);

	float DistanceTo(sf::Vector2f aWorldCoords);
	float DistanceSquaredTo(sf::Vector2f aWorldCoords);

	sf::Vector2f GetWorldCoords() { return mWorldCoords; }
	float GetMass() { return mMass; }
	float GetHitRadiusSquared() { return mHitRadius2; }

private:
	GameManager &mGameManager;

	sf::Vector2f &mWorldCoords;
	float mHitRadius2;
	float mMass;
};

