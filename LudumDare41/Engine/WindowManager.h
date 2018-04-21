#pragma once
#include <SFML/Graphics.hpp>

class GameManager;

class WindowManager
{
public:
	WindowManager(GameManager &aGameManager);
	~WindowManager();

	void SetDrawFocus(sf::Vector2f center);

	//Returns false if close is requested
	bool Update();

	sf::RenderWindow &GetWindow() { return mWindow; }

private:
	sf::RenderWindow mWindow;
	sf::View mView;
	sf::Sprite mHUD;

	GameManager &mGameManager;
};

#include "GameManager.h"

