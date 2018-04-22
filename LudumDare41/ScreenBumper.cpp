#include "ScreenBumper.h"



ScreenBumper::ScreenBumper(GameManager & aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mBump(),
	mVelocity(),
	mAccel(),
	mPullForce(),
	mHarmonicConstant(20.f),
	mDampingConstant(10)
{
}


ScreenBumper::~ScreenBumper()
{
}

bool ScreenBumper::Update(sf::Time dt)
{
	mAccel = -mBump * mHarmonicConstant + mPullForce;
	mAccel -= mVelocity * mDampingConstant;
	mVelocity = mVelocity + mAccel * dt.asSeconds();
	mBump = mBump + mVelocity * dt.asSeconds();
	mGameManager.GetWindowManager().SetScreenBump(mBump);
	return true;
}

void ScreenBumper::Bump(sf::Vector2f aImpact)
{
	mVelocity += aImpact;
}

void ScreenBumper::Pull(sf::Vector2f aForce)
{
	mPullForce = aForce;
}
