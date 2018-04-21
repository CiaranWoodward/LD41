#include "Player.h"



Player::Player(GameManager &aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mTextMessage("", mGameManager.GetDrawManager().GetGlobalFont(), 20),
	mCooldown(sf::Time::Zero),
	mTextCooldown(sf::seconds(5.f)),
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
	mGameManager.GetWindowManager().SetDrawFocus(mSprite.getPosition());

	return true;
}
