#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"
#include "../ParticleHelper.h"

class BloodSplatter :
	public LogicObject
{
public:
	BloodSplatter(GameManager & aGameManager, sf::Vector3f aStartPoint, sf::Vector3f aDirection);
	~BloodSplatter();

	bool Update(sf::Time dt) override;

private:
	GameManager &mGameManager;

	sf::Sprite mSprite;
	sf::Color mColor;
	sf::Sprite mShadowSprite;
	DrawObject mDrawObject;
	DrawObject mShadowDrawObject;
	ParticleHelper mParticleHelper;

	sf::Time mTimeout;
	float mDegreesPerSec;
};

