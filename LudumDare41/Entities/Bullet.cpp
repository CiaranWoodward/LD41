#include "Bullet.h"



Bullet::Bullet(GameManager & aGameManager, sf::Vector3f aStartPoint) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mParticleHelper(aStartPoint, sf::Vector3f(500.0f, 0.0f, 1.f), 0.5f, 0.001f)
{
	int randOffset = (std::rand() % 4) * 2;
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(0, 837 + randOffset, 2, 2));
	mSprite.setPosition(MapManager::GetProjectedCoords(aStartPoint));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(aStartPoint).y + aStartPoint.z));
}

Bullet::~Bullet()
{
}

bool Bullet::Update(sf::Time dt)
{
	sf::Vector3f newCoords = mParticleHelper.GetNewCoords(dt);
	
	mSprite.setPosition(MapManager::GetProjectedCoords(newCoords));
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(newCoords).y + newCoords.z));

	return true;
}
