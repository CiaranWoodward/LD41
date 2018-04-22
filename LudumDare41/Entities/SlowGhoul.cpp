#include "SlowGhoul.h"
#include "../VectorTools.h"
#include "BloodSplatter.h"

SlowGhoul::SlowGhoul(GameManager &aGameManager, Player &aPlayer) :
	LogicObject(aGameManager.GetLogicManager()),
	DamageTaker(),
	mGameManager(aGameManager),
	mTextCoords1(64, 253, 36, 67),
	mTextCoords2(64 + 54 * 1, 253, 36, 67),
	mTextCoords3(64 + 54 * 2, 253, 36, 67),
	mSprite(),
	mDrawObject(aGameManager.GetDrawManager(), mSprite, 0),
	mAnimCooldown(sf::seconds((float) (rand() % 200) / 100.f)),
	mDeathTimeout(sf::seconds(1.f)),
	mWorldPos(),
	mVelocity(),
	mRecoil(),
	mRecoilMag(),
	mSpeed(),
	mMaxSpeed(200.f),
	mAccel(1600.f),
	mHealth(100.f),
	mPlayer(aPlayer),
	mEnemyObject(mGameManager, *this, mWorldPos, 15.f, (float) rand() / 8192.f, 50.f)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(mTextCoords1);
	
	float r = 1500.f;
	float theta = rand() % 6283;
	theta /= 1000.f;
	mWorldPos = sf::Vector2f(r * sin(theta), r / 2.f * cos(theta)) + mPlayer.GetWorldCoords();
	mSprite.setPosition(mWorldPos);
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
}

SlowGhoul::~SlowGhoul()
{
}

bool SlowGhoul::Update(sf::Time dt)
{
	if (isDead())
	{
		mDeathTimeout -= dt;
		mSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(mDeathTimeout.asSeconds() * 255.f)));
		sf::Vector3f bloodpoint = MapManager::GetFloorCoords(mWorldPos);
		bloodpoint.z += 15.f;
		new BloodSplatter(mGameManager, bloodpoint, sf::Vector3f());
		bloodpoint.z += 15.f;
		new BloodSplatter(mGameManager, bloodpoint, sf::Vector3f());
		bloodpoint.z += 15.f;
		new BloodSplatter(mGameManager, bloodpoint, sf::Vector3f());
		if (mDeathTimeout < sf::Time::Zero)
			return false;
		return true;
	}

	HandleChase(dt);
	HandleAnimation(dt);
	mVelocity -= mRecoil * mRecoilMag;
	mRecoilMag -= mRecoilMag * 25.f * dt.asSeconds();
	mWorldPos += mVelocity * dt.asSeconds();
	mSprite.setPosition(mWorldPos);
	mDrawObject.SetDrawLevel(mSprite.getPosition().y - 5);

	return true;
}

void SlowGhoul::HandleAnimation(sf::Time dt)
{
	mAnimCooldown += dt;

	if (mAnimCooldown.asSeconds() < 0.5f)
	{
		mSprite.setTextureRect(mTextCoords1);
	}
	else if (mAnimCooldown.asSeconds() < 1.f)
	{
		mSprite.setTextureRect(mTextCoords2);
	}
	else if (mAnimCooldown.asSeconds() < 1.5f)
	{
		mSprite.setTextureRect(mTextCoords1);
	}
	else if (mAnimCooldown.asSeconds() < 2.f)
	{
		mSprite.setTextureRect(mTextCoords3);
	}
	else
	{
		mAnimCooldown = sf::Time::Zero;
	}
}

float SlowGhoul::EvaluateDamage(float aDamage, sf::Vector3f aImpactPoint)
{
	float actDamage = aDamage - 2.f;
	if (actDamage < 0) actDamage = 0.f;
	return actDamage;
}

bool SlowGhoul::TakeDamage(float aDamage, sf::Vector3f aImpactPoint, sf::Vector3f aVelocity)
{
	new BloodSplatter(mGameManager, aImpactPoint, aVelocity);
	new BloodSplatter(mGameManager, aImpactPoint, aVelocity);
	new BloodSplatter(mGameManager, aImpactPoint, aVelocity);
	new BloodSplatter(mGameManager, aImpactPoint, aVelocity);
	mRecoilMag = VectorTools::Normalize(aVelocity);
	mRecoilMag = aDamage * 80.f;
	mRecoil = -sf::Vector2f(aVelocity.x, aVelocity.y/2.f);
	mHealth -= EvaluateDamage(aDamage, aImpactPoint);
	return (mHealth < 0);
}

void SlowGhoul::HandleChase(sf::Time dt)
{
	sf::Vector2f dir = mPlayer.GetWorldCoords() - mWorldPos;

	//Normalize direction
	float mag = std::sqrtf(dir.x * dir.x + dir.y * dir.y);
	if (mag > 0)
	{
		dir = (dir / mag);
		dir.y /= 2; //correct y movement for dimetric projection
		mSpeed += mAccel * dt.asSeconds();
	}
	else
	{
		mSpeed -= mAccel * dt.asSeconds();
	}
	if (mSpeed > mMaxSpeed) mSpeed = mMaxSpeed;
	if (mSpeed < 0) mSpeed = 0.f;
	mVelocity = dir * mSpeed;
}
