#include "DeathFarm.h"



DeathFarm::DeathFarm(GameManager & aGameManager, sf::Vector2f aCoord) :
	LogicObject(aGameManager.GetLogicManager()),
	mCoords(aCoord),
	mGameManager(aGameManager),
	mSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mEnemyObject(mGameManager, *this, mCoords, 15.f, FLT_MAX, 30.f),
	mTimeout(sf::seconds(20))
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(216, 243, 54, 53));
	mSprite.setPosition(aCoord);
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(aCoord.y) - 8.f);
}


DeathFarm::~DeathFarm()
{
}

bool DeathFarm::Update(sf::Time dt)
{
	if (mTimeout > sf::seconds(-11.f))
		mTimeout -= dt;

	if (mTimeout > sf::seconds(16.f))
	{
		mSprite.setTextureRect(sf::IntRect(216, 243, 54, 53));
	}
	else if (mTimeout > sf::seconds(12.f))
	{
		mSprite.setTextureRect(sf::IntRect(216 + 54 * 1, 243, 54, 53));
	}
	else if (mTimeout > sf::seconds(8.f))
	{
		mSprite.setTextureRect(sf::IntRect(216 + 54 * 2, 243, 54, 53));
	}
	else if (mTimeout > sf::seconds(4.f))
	{
		mSprite.setTextureRect(sf::IntRect(216 + 54 * 3, 243, 54, 53));
	}
	else if (mTimeout > sf::seconds(-10.f))
	{
		mSprite.setTextureRect(sf::IntRect(216 + 54 * 4, 243, 54, 53));
	}
	else
	{
		mSprite.setTextureRect(sf::IntRect(216 + 54 * 5, 243, 54, 53));
	}

	return true;
}

float DeathFarm::EvaluateDamage(float aDamage, sf::Vector3f aImpactPoint)
{
	return 0.0f;
}

bool DeathFarm::TakeDamage(float aDamage, sf::Vector3f aImpactPoint, sf::Vector3f aVelocity)
{
	return false;
}
