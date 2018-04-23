#pragma once
#include <SFML/Graphics.hpp>

class GameManager;

class WindowManager
{
public:
	WindowManager(GameManager &aGameManager);
	~WindowManager();

	void SetDrawFocus(sf::Vector2f aCenter) { mFocusPoint = aCenter; }
	void SetScreenBump(sf::Vector2f aBump) { mScreenBump = aBump;  }

	//Returns false if close is requested
	bool Update();

	sf::RenderWindow &GetWindow() { return mWindow; }

	sf::Vector2f GetWorldCoordsFromWindow(sf::Vector2i aWindowCoords);

private:
	sf::RenderWindow mWindow;
	sf::View mView;
	sf::Sprite mHUD;
	sf::Vector2f mDimens;
	sf::Vector2f mFocusPoint;
	sf::Vector2f mScreenBump;

	sf::Text mAmmoDisplay;

	GameManager &mGameManager;
};

#include "GameManager.h"

