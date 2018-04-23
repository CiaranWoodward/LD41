#include "DeathFarm.h"
#include "../VectorTools.h"
#include "Player.h"


DeathFarm::DeathFarm(GameManager & aGameManager, sf::Vector2f aCoord) :
	LogicObject(aGameManager.GetLogicManager()),
	mCoords(aCoord),
	mGameManager(aGameManager),
	mSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mEnemyObject(mGameManager, *this, mCoords, 15.f, FLT_MAX, 30.f),
	mTimeout(sf::seconds(20)),
	mBestTime(mTimeout),
	mDeathFade(sf::seconds(1)),
	mDead(false),
	mSufficient(false)
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
	bool ripe = false;
	if (mTimeout > sf::seconds(-11.f))
	{
		if (mSufficient)
			mTimeout -= dt;
		else
			mTimeout += dt;
	}

	if (mTimeout > sf::seconds(16.f) || mDead)
	{
		if(mBestTime.asSeconds() < 8.f)
			mSprite.setTextureRect(sf::IntRect(216 + 54 * 5, 243, 54, 53));
		else
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
	else if (mTimeout > sf::seconds(-20.f))
	{
		mSprite.setTextureRect(sf::IntRect(216 + 54 * 4, 243, 54, 53));
		ripe = true;
	}
	else
	{
		mSprite.setTextureRect(sf::IntRect(216 + 54 * 5, 243, 54, 53));
	}

	if (ripe)
	{
		Player &player = mGameManager.GetPlayer();
		sf::Vector2f displace = mCoords - player.GetWorldCoords();
		float dist = VectorTools::Normalize(displace);

		if (dist < 40.f)
		{
			//Harvest
			mTimeout = sf::seconds(-20.f);
			player.mCobs += 3;
			mGameManager.IncrementHarvests(3);
		}
	}

	if (mBestTime > mTimeout)
		mBestTime = mTimeout;

	if (mBestTime.asSeconds() < 8.f)
		mSufficient = true;

	if (mTimeout > sf::seconds(60))
	{
		mDead = true;
	}

	if (mDead)
	{
		mDeathFade -= dt;
		float fade = mDeathFade.asSeconds();
		if (fade < 0)
			return false;
		mSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(fade * 255.f)));
	}

	return true;
}

float DeathFarm::EvaluateDamage(float aDamage, sf::Vector3f aImpactPoint)
{
	if(!mDead && !mSufficient)
		return aDamage < 0.f ? aDamage : 0.f;
	return 0.f;
}

bool DeathFarm::TakeDamage(float aDamage, sf::Vector3f aImpactPoint, sf::Vector3f aVelocity)
{
	mTimeout += sf::seconds(EvaluateDamage(aDamage, aImpactPoint) / 2.f);
	return mDead;
}
