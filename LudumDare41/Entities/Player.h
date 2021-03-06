#pragma once

#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"
#include "../Engine/TileObject.h"
#include "../Engine/DrawObject.h"
#include "../ScreenBumper.h"

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

	sf::Vector2f GetWorldCoords();

	int mCobs;
	int mKernels;

	float mHealth;

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
	sf::Vector2f mRecoil;
	float mRecoilMag;
	float mSpeed;
	float mMaxSpeed;
	float mAccel;

	DrawObject mDrawObject;
	DrawObject mDrawTextObject;

	ScreenBumper *mScreenBumper;

	sf::Time mWaveCooldown;
	sf::Time mMicroWave;
	int mWaveCount;
	int mMicroWaveCount;

	void TrapOnMap();

	void HandleWaves(sf::Time dt);
};

