#include <cstdlib>

#include "Player.h"
#include "CornBullet.h"
#include "BloodSplatter.h"

#include "SFML\Window\Keyboard.hpp"
#include "SFML\Window\Mouse.hpp"


Player::Player(GameManager &aGameManager, Crosshair &aCrosshair) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mCrosshair(aCrosshair),
	mTextCoordsUp(0, 81*3, 53, 81),
	mTextCoordsDown(0, 81, 53, 81),
	mTextCoordsLeft(0, 81*2, 53, 81),
	mTextCoordsRight(0, 0, 53, 81),
	mSprite(),
	mTextMessage("", mGameManager.GetDrawManager().GetGlobalFont(), 20),
	mCooldown(sf::Time::Zero),
	mTriggerLastState(false),
	mTextCooldown(sf::seconds(5.f)),
	mVelocity(),
	mSpeed(0.f),
	mMaxSpeed(300.f),
	mAccel(1600.f),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mTextCounter(0),
	mDrawTextObject(mGameManager.GetDrawManager(), mTextMessage, INT32_MAX),
	mScreenBumper(new ScreenBumper(aGameManager))
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
	HandleMouseInput(dt);

	mSprite.move(mVelocity * dt.asSeconds());
	mDrawObject.SetDrawLevel(mSprite.getPosition().y - 5);

	TrapOnMap();

	mGameManager.GetWindowManager().SetDrawFocus(mSprite.getPosition());

	return true;
}

void Player::TrapOnMap()
{
	//Confine player to map
	sf::Vector2f world = mSprite.getPosition();
	sf::Vector2f transformed(2.f * world.y + world.x, 2.f * world.y - world.x);
	bool transformBack = false;
	if (transformed.x < 0)
	{
		transformed.x = 0;
		transformBack = true;
	}
	if (transformed.y < 0)
	{
		transformed.y = 0;
		transformBack = true;
	}
	if (transformed.x > 2.f * (MapManager::kMaxX-1) * MapManager::kTileWidth)
	{
		transformed.x = 2.f * (MapManager::kMaxX-1) * MapManager::kTileWidth;
		transformBack = true;
	}
	if (transformed.y > 4.f * (MapManager::kMaxY-1) * MapManager::kTileHeight)
	{
		transformed.y = 4.f * (MapManager::kMaxY-1) * MapManager::kTileHeight;
		transformBack = true;
	}
	if (transformBack)
	{
		world = sf::Vector2f((transformed.x - transformed.y) / 2.f, (transformed.x + transformed.y) / 4.f);
		mSprite.setPosition(world);
	}
}

void Player::HandleMouseInput(sf::Time dt)
{
	bool shoot = false;
	sf::Vector3f gunCoords = MapManager::GetFloorCoords(mSprite.getPosition() - sf::Vector2f(0.f, 5.f));
	gunCoords.z += 44;
	sf::Vector3f shootDir = mCrosshair.GetTarget() - gunCoords;
	float mag = std::sqrtf(shootDir.x * shootDir.x + shootDir.y * shootDir.y + shootDir.z * shootDir.z);

	mCrosshair.SetHeight(mag / 10.f);

	if (abs(shootDir.x) > abs(shootDir.y))
	{
		if (shootDir.x > 0)
			mSprite.setTextureRect(mTextCoordsRight);
		else
			mSprite.setTextureRect(mTextCoordsLeft);
	}
	else
	{
		if (shootDir.y > 0)
			mSprite.setTextureRect(mTextCoordsDown);
		else
			mSprite.setTextureRect(mTextCoordsUp);
	}

	mScreenBumper->Pull(sf::Vector2f(shootDir.x, shootDir.y / 2.f) * 5.f);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!mTriggerLastState)
		{
			mTriggerLastState = true;
			//Shoot single shot weapons
		}

		if (true) //automatic weapons
		{
			shoot = true;
		}
	}
	else
	{
		mTriggerLastState = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		shoot = false;
		new BloodSplatter(mGameManager, gunCoords, shootDir * 1000.f / mag);
		new BloodSplatter(mGameManager, gunCoords, shootDir * 1000.f / mag);
	}

	if (mCooldown > sf::Time::Zero)
	{
		mCooldown -= dt;
	}
	else if (shoot)
	{
		sf::Vector3f gunSpeed(mVelocity.x, mVelocity.y * 2, 0.f);

		if (mag > 0)
		{
			shootDir = shootDir / mag;

			mCooldown = sf::Time::Zero;

			mRecoil = sf::Vector2f(shootDir.x, shootDir.y/2.f);
			mRecoilMag = 50.f;
			mScreenBumper->Bump(mRecoil * mRecoilMag);
			new CornBullet(mGameManager, gunCoords, gunSpeed, shootDir);
			//mCooldown = sf::seconds(0.1f);
		}
	}

	mVelocity -= mRecoil * mRecoilMag;
	mRecoilMag -= mRecoilMag * 20.f * dt.asSeconds();
	if (mRecoilMag < 0) mRecoilMag = 0;
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
}

sf::Vector2f Player::GetWorldCoords()
{
	return mSprite.getPosition();
}
