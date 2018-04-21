#pragma once

#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"
#include "../Engine/TileObject.h"
#include "../Engine/DrawObject.h"

#include "Crosshair.h"

class Player :
	public LogicObject
{
public:
	Player(GameManager &aGameManager, Crosshair &aCrosshair);
	~Player();

	bool Update(sf::Time dt) override;

	void HandleMouseInput(sf::Time dt);

	void HandleKeyboardInput(sf::Time dt);

private:
	GameManager &mGameManager;
	Crosshair &mCrosshair;

	const sf::IntRect mTextCoordsUp, mTextCoordsRight, mTextCoordsDown, mTextCoordsLeft;
	sf::Sprite mSprite;
	sf::Text mTextMessage;

	sf::Time mCooldown;
	bool mTriggerLastState;
	sf::Time mTextCooldown;

	int mTextCounter;

	bool isGameOver;
	uint32_t score;

	sf::Vector2f mVelocity;
	float mSpeed;
	float mMaxSpeed;
	float mAccel;

	DrawObject mDrawObject;
	DrawObject mDrawTextObject;
};

