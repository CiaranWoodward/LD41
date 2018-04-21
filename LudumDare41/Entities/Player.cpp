#include <cstdlib>

#include "Player.h"
#include "Bullet.h"

#include "SFML\Window\Keyboard.hpp"


Player::Player(GameManager &aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mTextMessage("", mGameManager.GetDrawManager().GetGlobalFont(), 20),
	mCooldown(sf::Time::Zero),
	mTextCooldown(sf::seconds(5.f)),
	mVelocity(),
	mSpeed(0.f),
	mMaxSpeed(300.f),
	mAccel(1600.f),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mTextCounter(0),
	mDrawTextObject(mGameManager.GetDrawManager(), mTextMessage, INT32_MAX)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(0, 0, 53, 81));
	mSprite.setPosition(MapManager::GetTileDrawOrigin(sf::Vector2u(20,20)));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetTileDrawOrigin(sf::Vector2u(50, 50)).y));

	mTextMessage.setPosition(mSprite.getPosition() - sf::Vector2f(0.f, 75.f));
	mTextMessage.setOrigin(mTextMessage.getLocalBounds().width / 2, 0);
	mTextMessage.setFillColor(sf::Color::White);
}


Player::~Player()
{
}

bool Player::Update(sf::Time dt)
{
	HandleKeyboardInput(dt);

	mGameManager.GetWindowManager().SetDrawFocus(mSprite.getPosition());
	
	if (mCooldown > sf::Time::Zero)
	{
		mCooldown -= dt;
	}
	else
	{
		sf::Vector3f mGunCoords = MapManager::GetFloorCoords(mSprite.getPosition() - sf::Vector2f(0.f, 5.f));
		sf::Vector3f mGunSpeed(mVelocity.x, mVelocity.y * 2, 0.f);
		mGunCoords.z += 44;
		mCooldown = sf::Time::Zero;
		new Bullet(mGameManager, mGunCoords, mGunSpeed);
		mCooldown = sf::seconds(0.2f);
	}

	return true;
}

void Player::HandleKeyboardInput(sf::Time dt)
{
	sf::Vector2f dir;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		dir.y -= 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		dir.x -= 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		dir.y += 1.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		dir.x += 1.f;
	}

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

	mSprite.move(mVelocity * dt.asSeconds());
}
