#pragma once
#include "../Engine/GameManager.h"
#include "../Engine/LogicObject.h"
#include "../ParticleHelper.h"

class CornBullet :
	public LogicObject
{
public:
	CornBullet(GameManager &aGameManager, sf::Vector3f aStartPoint, sf::Vector3f aBaseVelocity, sf::Vector3f aDirection);
	~CornBullet();

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

