#pragma once
#include "../Engine/LogicObject.h"
#include "../Engine/EnemyObject.h"
#include "../Engine/GameManager.h"
#include "../DamageTaker.h"

#include "Player.h"

class SlowGhoul :
	public LogicObject, DamageTaker
{
public:
	SlowGhoul(GameManager &aGameManager, Player &aPlayer);
	~SlowGhoul();

	bool Update(sf::Time dt) override;

	float EvaluateDamage(float aDamage, sf::Vector3f aImpactPoint) override;
	bool TakeDamage(float aDamage, sf::Vector3f aImpactPoint, sf::Vector3f aVelocity) override;
	bool isDead() override { return mHealth < 0; }

private:
	GameManager &mGameManager;

	const sf::IntRect mTextCoords1, mTextCoords2, mTextCoords3;
	sf::Sprite mSprite;
	DrawObject mDrawObject;
	sf::Time mAnimCooldown;
	sf::Time mDeathTimeout;

	sf::Vector2f mWorldPos;
	sf::Vector2f mVelocity;
	sf::Vector2f mRecoil;
	float mRecoilMag;
	float mSpeed;
	float mMaxSpeed;
	float mAccel;
	float mHealth;

	Player &mPlayer;
	EnemyObject mEnemyObject;

	void HandleChase(sf::Time dt);
	void HandleAnimation(sf::Time dt);

	bool mFarmPlaced;
};

