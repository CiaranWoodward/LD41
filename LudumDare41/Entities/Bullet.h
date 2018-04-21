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
	sf::Vector3f GetRandomScatter(float scatterval);

	GameManager &mGameManager;

	sf::Sprite mSprite;
	sf::Sprite mShadowSprite;
	DrawObject mDrawObject;
	DrawObject mShadowDrawObject;
	ParticleHelper mParticleHelper;
};

