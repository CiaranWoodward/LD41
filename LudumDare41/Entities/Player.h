#pragma once

#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"
#include "../Engine/TileObject.h"
#include "../Engine/DrawObject.h"

class Player :
	public LogicObject
{
public:
	Player(GameManager &aGameManager);
	~Player();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;
	sf::Text mTextMessage;

	sf::Time mCooldown;
	sf::Time mTextCooldown;

	int mTextCounter;

	bool isGameOver;
	uint32_t score;

	DrawObject mDrawObject;
	DrawObject mDrawTextObject;
};

