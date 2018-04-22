#include <cassert>

#include "ParticleHelper.h"

const float ParticleHelper::kGravity = 100.f;

ParticleHelper::ParticleHelper(sf::Vector3f aStartPos, sf::Vector3f aStartVelocity, float aBounceFactor, float aFrictionFactor, float aAirResFactor) :
	mCoords(aStartPos),
	mVelocity(aStartVelocity),
	mBounceFactor(aBounceFactor),
	mFrictionFactor(aFrictionFactor),
	mAirResFactor(aAirResFactor),
	mDead(false)
{
	assert(aBounceFactor > 0);
}


ParticleHelper::~ParticleHelper()
{
}

sf::Vector3f ParticleHelper::GetNewCoords(sf::Time dt)
{
	if (mDead) return mCoords;
	//Apply velocity
	mCoords = mCoords + (mVelocity * dt.asSeconds());

	//Apply bounce
	if (mCoords.z < 0)
	{
		mVelocity.z = -mVelocity.z * mBounceFactor;
		mCoords.z = -mCoords.z * mBounceFactor;
		mVelocity = mVelocity * mFrictionFactor;
	}

	//Apply air resistance
	sf::Vector3f vv = mVelocity;
	vv.x *= vv.x;
	vv.y *= vv.y;
	vv.z *= vv.z;
	if (mVelocity.x < 0) vv.x = -vv.x;
	if (mVelocity.y < 0) vv.y = -vv.y;
	if (mVelocity.z < 0) vv.z = -vv.z;

	mVelocity -= ((vv * mAirResFactor) * dt.asSeconds());

	//Apply gravity
	mVelocity.z -= kGravity * dt.asSeconds();

	if (mCoords.z < 0.2f && vv.x < 0.2f && vv.y < 0.2f && vv.z < 0.2f)
		mDead = true;

	return mCoords;
}
