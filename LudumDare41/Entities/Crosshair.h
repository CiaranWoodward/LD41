#pragma once

#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"

class Crosshair :
	public LogicObject
{
public:
	Crosshair(GameManager &aGameManager);
	~Crosshair();

	bool Update(sf::Time dt) override;

	sf::Vector3f GetTarget();

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;
	DrawObject mDrawObject;
};

