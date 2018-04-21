#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"
#include "../ParticleHelper.h"

class Bullet :
	public LogicObject
{
public:
	Bullet(GameManager &aGameManager, sf::Vector3f aStartPoint);
	~Bullet();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;
	DrawObject mDrawObject;
	ParticleHelper mParticleHelper;
};

