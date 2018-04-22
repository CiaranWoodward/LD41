#include "WindowManager.h"
#include "MapManager.h"

WindowManager::WindowManager(GameManager &aGameManager) :
	mWindow(sf::VideoMode(1280, 720), "Ludum Dare 41"),
	mGameManager(aGameManager),
	mHUD(),
	mDimens(1280.f, 720.f),
	mFocusPoint(),
	mScreenBump()
{
	sf::Vector2f center = MapManager::GetTileDrawCenter(sf::Vector2<uint32_t>(MapManager::kMaxX/2, MapManager::kMaxY/2));
	mView = sf::View(center, mDimens);
	mWindow.setView(mView);
	mWindow.setFramerateLimit(60);
	mWindow.setMouseCursorVisible(false);

	mHUD.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mHUD.setTextureRect(sf::IntRect(1473, 177, 255, 687));
	mHUD.setPosition(1280, 720);
	mHUD.setOrigin(mHUD.getTextureRect().width, mHUD.getTextureRect().height);
	mHUD.setScale(0.5f, 0.5f);
}


WindowManager::~WindowManager()
{
}

bool WindowManager::Update()
{
	if (!mWindow.isOpen()) return false;

	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();

		if (event.type == sf::Event::MouseButtonPressed)
			void;

		if (event.type == sf::Event::MouseButtonReleased)
			void;

	}

	mView.setCenter(mFocusPoint + mScreenBump);

	mWindow.clear(sf::Color(126, 75, 50));
	mWindow.setView(mView);
	mGameManager.GetDrawManager().DrawAll(mWindow);
	mWindow.setView(mWindow.getDefaultView());
	mWindow.draw(mHUD);
	mWindow.setView(mView);
	mWindow.display();
	
	return true;
}

sf::Vector2f WindowManager::GetWorldCoordsFromWindow(sf::Vector2i aWindowCoords)
{
	return mWindow.mapPixelToCoords(aWindowCoords);
}
