#include "BloodSplatter.h"
#include "../VectorTools.h"

BloodSplatter::BloodSplatter(GameManager & aGameManager, sf::Vector3f aStartPoint, sf::Vector3f aDirection) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mColor(200 + rand() % 55, 200 + rand() % 55, 200 + rand() % 55, 255),
	mShadowSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mShadowDrawObject(mGameManager.GetDrawManager(), mShadowSprite, 0),
	mParticleHelper(aStartPoint + VectorTools::GetRandomScatter(5.f), aDirection / 5.f + VectorTools::GetRandomScatter(40.f), 0.6f, 0.2f, 0.01f),
	mTimeout(sf::seconds(12)),
	mDegreesPerSec(rand() % 120 - 60)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(222, 296, 16, 16));
	mSprite.setPosition(MapManager::GetProjectedCoords(aStartPoint));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height / 2.f);
	mSprite.setRotation(rand() % 360);
	mSprite.setColor(mColor);
	mShadowSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mShadowSprite.setTextureRect(sf::IntRect(222, 315, 16, 9));
	mShadowSprite.setPosition(MapManager::GetProjectedCoords(aStartPoint - sf::Vector3f(0.f, 0.f, aStartPoint.z)));
	mShadowSprite.setOrigin(mShadowSprite.getTextureRect().width / 2.f, mShadowSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(aStartPoint).y + aStartPoint.z));
	mShadowDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(aStartPoint).y - 1));
}


BloodSplatter::~BloodSplatter()
{
}

bool BloodSplatter::Update(sf::Time dt)
{
	sf::Vector3f newCoords = mParticleHelper.GetNewCoords(dt);

	mSprite.setPosition(MapManager::GetProjectedCoords(newCoords));
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(newCoords).y + newCoords.z));

	if (!mParticleHelper.IsDead())
	{
		mSprite.rotate(mDegreesPerSec * dt.asSeconds());
		mShadowSprite.setPosition(MapManager::GetProjectedCoords(newCoords - sf::Vector3f(0.f, 0.f, newCoords.z)));
		mShadowDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(newCoords).y - 1));
	}
	else
	{
		mShadowDrawObject.SetDrawLevel(INT_MIN);
		mShadowDrawObject.SetInactive(true);
	}

	mTimeout -= dt;

	if (mTimeout > sf::seconds(11.8))
	{
		mSprite.setTextureRect(sf::IntRect(222, 296, 16, 16));
		mShadowSprite.setTextureRect(sf::IntRect(222, 315, 16, 9));
	}
	else if (mTimeout > sf::seconds(11.6))
	{
		mSprite.setTextureRect(sf::IntRect(237, 296, 16, 16));
		mShadowSprite.setTextureRect(sf::IntRect(237, 315, 16, 9));
	}
	else if (mTimeout > sf::seconds(11.4))
	{
		mSprite.setTextureRect(sf::IntRect(251, 296, 16, 16));
		mShadowSprite.setTextureRect(sf::IntRect(251, 315, 16, 9));
	}
	else if (mTimeout > sf::seconds(11.0))
	{
		mSprite.setTextureRect(sf::IntRect(269, 296, 16, 16));
		mShadowSprite.setTextureRect(sf::IntRect(269, 315, 16, 9));
	}
	else
	{
		mSprite.setTextureRect(sf::IntRect(286, 296, 16, 16));
		mShadowSprite.setTextureRect(sf::IntRect(286, 315, 16, 9));
	}


	if (mTimeout < sf::seconds(2.f))
	{
		mColor.a = mTimeout.asSeconds() * 127.f;
		mSprite.setColor(mColor);
		mShadowSprite.setColor(sf::Color::Transparent);
	}
	if (mTimeout <= sf::Time::Zero)
	{
		return false;
	}

	return true;
}
