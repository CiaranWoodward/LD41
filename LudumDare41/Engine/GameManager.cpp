#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "DrawObject.h"

#include "../Entities/Player.h"
#include "../Entities/PlainTiles.h"

GameManager::GameManager() :
	mDrawManager(),
	mWindowManager(*this),
	mLogicManager(),
	mEnemyManager(mCorpseCounter, mCorpseTotal),
	mCorpseCounter(4),
	mCorpseTotal(4),
	mGrainCounter(20)
{
	std::srand(std::time(0));
}


GameManager::~GameManager()
{
	
}

int GameManager::run()
{
	bool run = true;
	
	new PlainTiles(*this);
	new Player(*this);
	
	while (run)
	{
		run = run && mWindowManager.Update();
		run = run && mMapManager.Update();
		run = run && mLogicManager.Update();
		run = run && mEnemyManager.Update();
	}
	return 0;
}
