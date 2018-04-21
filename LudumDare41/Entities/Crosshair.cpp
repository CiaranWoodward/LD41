#include "Crosshair.h"
#include "SFML\Window\Mouse.hpp"



Crosshair::Crosshair(GameManager &aGameManager) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0)
{
	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(63, 817, 9, 45));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, 3);
}


Crosshair::~Crosshair()
{
}

bool Crosshair::Update(sf::Time dt)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(mGameManager.GetWindowManager().GetWindow());
	sf::Vector2f worldCoords = mGameManager.GetWindowManager().GetWorldCoordsFromWindow(mousePos);

	mSprite.setPosition(worldCoords);
	mDrawObject.SetDrawLevel(worldCoords.y + 41);

	return true;
}

sf::Vector3f Crosshair::GetTarget()
{
	sf::Vector3f coords = MapManager::GetFloorCoords(mSprite.getPosition() + sf::Vector2f(0.f, 41.f));
	coords += sf::Vector3f(0.f, 0.f, 41.f);

	return coords;
}
