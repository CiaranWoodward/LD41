#include "Crosshair.h"
#include "SFML\Window\Mouse.hpp"

Crosshair::Crosshair(GameManager &aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	SetHeight(50.f);
}


Crosshair::~Crosshair()
{
}

bool Crosshair::Update(sf::Time dt)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(mGameManager.GetWindowManager().GetWindow());
	sf::Vector2f worldCoords = mGameManager.GetWindowManager().GetWorldCoordsFromWindow(mousePos);

	mSprite.setPosition(worldCoords);
	mDrawObject.SetDrawLevel(worldCoords.y + static_cast<int>(mHeight));

	return true;
}

void Crosshair::SetHeight(float aHeight)
{
	if (aHeight > 78.f) aHeight = 78.f;
	if (aHeight < 0.f) aHeight = 0.f;
	mHeight = aHeight;
	mSprite.setTextureRect(sf::IntRect(63, 783, 9, mHeight + 2.f));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, 2.f);
}

sf::Vector3f Crosshair::GetTarget()
{
	sf::Vector3f coords = MapManager::GetFloorCoords(mSprite.getPosition() + sf::Vector2f(0.f, mHeight));
	coords += sf::Vector3f(0.f, 0.f, mHeight);

	return coords;
}
