#include "SlowGhoul.h"
#include "../VectorTools.h"


SlowGhoul::SlowGhoul(GameManager &aGameManager, Player &aPlayer) :
	LogicObject(aGameManager.GetLogicManager()),
	DamageTaker(),
	mGameManager(aGameManager),
	mTextCoords1(64, 253, 36, 67),
	mTextCoords2(64 + 54 * 1, 253, 36, 67),
	mTextCoords3(64 + 54 * 2, 253, 36, 67),
	mSprite(),
	mDrawObject(aGameManager.GetDrawManager(), mSprite, 0),
	mAnimCooldown(sf::seconds(0.3f)),
	mWorldPos(),
	mVelocity(),
	mRecoil(),
	mRecoilMag(),
	mSpeed(),
	mMaxSpeed(250.f),
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
	HandleChase(dt);
	mVelocity -= mRecoil * mRecoilMag;
	mRecoilMag -= mRecoilMag * 20.f * dt.asSeconds();
	mWorldPos += mVelocity * dt.asSeconds();
	mSprite.setPosition(mWorldPos);
	mDrawObject.SetDrawLevel(mSprite.getPosition().y - 5);

	return !isDead();
}

float SlowGhoul::EvaluateDamage(float aDamage, sf::Vector3f aImpactPoint)
{
	float actDamage = aDamage - 2.f;
	if (actDamage < 0) actDamage = 0.f;
	return actDamage;
}

bool SlowGhoul::TakeDamage(float aDamage, sf::Vector3f aImpactPoint, sf::Vector3f aVelocity)
{
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
