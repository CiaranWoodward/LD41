#pragma once
#include "../Engine/LogicObject.h"
#include "../Engine/EnemyObject.h"
#include "../Engine/GameManager.h"

#include "Player.h"

class SlowGhoul :
	public LogicObject
{
public:
	SlowGhoul(GameManager &aGameManager, Player &aPlayer);
	~SlowGhoul();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	const sf::IntRect mTextCoords1, mTextCoords2, mTextCoords3;
	sf::Sprite mSprite;
	DrawObject mDrawObject;
	sf::Time mAnimCooldown;

	sf::Vector2f mWorldPos;
	sf::Vector2f mVelocity;
	sf::Vector2f mRecoil;
	float mRecoilMag;
	float mSpeed;
	float mMaxSpeed;
	float mAccel;

	Player &mPlayer;
	EnemyObject mEnemyObject;

	void HandleChase(sf::Time dt);
};

