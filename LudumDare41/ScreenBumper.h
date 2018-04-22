#pragma once
#include "Engine/LogicObject.h"
#include "Engine/GameManager.h"

class ScreenBumper :
	public LogicObject
{
public:
	ScreenBumper(GameManager & aGameManager);
	~ScreenBumper();

	bool Update(sf::Time dt) override;
	
	void Bump(sf::Vector2f aImpact);
	void Pull(sf::Vector2f aForce);

private:
	GameManager &mGameManager;

	sf::Vector2f mBump;
	sf::Vector2f mVelocity;
	sf::Vector2f mAccel;
	sf::Vector2f mPullForce;
	float mHarmonicConstant;
	float mDampingConstant;
};

