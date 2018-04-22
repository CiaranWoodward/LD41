#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class DeathFarm :
	public LogicObject, DamageTaker
{
public:
	DeathFarm(GameManager & aGameManager, sf::Vector2f aCoord);
	~DeathFarm();

	bool Update(sf::Time dt) override;

	float EvaluateDamage(float aDamage, sf::Vector3f aImpactPoint) override;
	bool TakeDamage(float aDamage, sf::Vector3f aImpactPoint, sf::Vector3f aVelocity) override;
	bool isDead() override { return false; }

private:
	GameManager &mGameManager;

	sf::Vector2f mCoords;

	sf::Sprite mSprite;
	DrawObject mDrawObject;

	EnemyObject mEnemyObject; //shhh... it works

	sf::Time mTimeout;
};

