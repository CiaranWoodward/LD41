#include "Bullet.h"

Bullet::Bullet(GameManager & aGameManager, sf::Vector3f aStartPoint, sf::Vector3f aBaseVelocity, sf::Vector3f aDirection) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mShadowSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mShadowDrawObject(mGameManager.GetDrawManager(), mShadowSprite, 0),
	mParticleHelper(aStartPoint, 800.f * aDirection + GetRandomScatter(40.f) + aBaseVelocity, 0.5f, 0.2f, 0.001f)
{
	int randOffset = (std::rand() % 4) * 2;

	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(0, 837 + randOffset, 2, 2));
	mSprite.setPosition(MapManager::GetProjectedCoords(aStartPoint));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mShadowSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mShadowSprite.setTextureRect(sf::IntRect(0, 845, 2, 2));
	mShadowSprite.setPosition(MapManager::GetProjectedCoords(aStartPoint - sf::Vector3f(0.f, 0.f, aStartPoint.z)));
	mShadowSprite.setOrigin(mShadowSprite.getTextureRect().width / 2.f, mShadowSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(aStartPoint).y + aStartPoint.z));
	mShadowDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(aStartPoint).y - 1));
}

Bullet::~Bullet()
{
}

bool Bullet::Update(sf::Time dt)
{
	sf::Vector3f newCoords = mParticleHelper.GetNewCoords(dt);
	
	mSprite.setPosition(MapManager::GetProjectedCoords(newCoords));
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(newCoords).y + newCoords.z));
	mShadowSprite.setPosition(MapManager::GetProjectedCoords(newCoords - sf::Vector3f(0.f, 0.f, newCoords.z)));
	mShadowDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(newCoords).y - 1));

	return true;
}

sf::Vector3f Bullet::GetRandomScatter(float scatterval)
{
	sf::Vector3f scatter;
	scatter.x = -scatterval + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * scatterval)));
	scatter.y = -scatterval + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * scatterval)));
	scatter.z = -scatterval + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2 * scatterval)));
	return scatter;
}
