#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>

#include "GameManager.h"
#include "DrawObject.h"

#include "../Entities/PlainTiles.h"
#include "../Entities/PlayerChair.h"
#include "../Entities/GrainPile.h"
#include "../Entities/CorpsePile.h"
#include "../Entities/Wall.h"
#include "../Entities/Farm.h"
#include "../Entities/Cursor.h"
#include "../Entities/EnemySpawner.h"

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
	delete mCursor;
}

int GameManager::run()
{
	bool run = true;
	
	
	while (run)
	{
		run = run && mWindowManager.Update();
		run = run && mMapManager.Update();
		run = run && mLogicManager.Update();
		run = run && mEnemyManager.Update();
	}
	return 0;
}
