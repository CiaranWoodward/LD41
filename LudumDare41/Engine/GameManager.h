#pragma once

#include "DrawManager.h"
#include "WindowManager.h"
#include "LogicManager.h"
#include "MapManager.h"
#include "EnemyManager.h"


class Cursor;
class Player;

class GameManager
{
public:
	GameManager();
	~GameManager();

	int run();

	MapManager &GetMapManager() { return mMapManager; }
	LogicManager &GetLogicManager() { return mLogicManager; }
	DrawManager &GetDrawManager() { return mDrawManager; }
	EnemyManager &GetEnemyManager() { return mEnemyManager; }
	WindowManager &GetWindowManager() { return mWindowManager; }

	uint32_t GetDifficulty() { return mCorpseTotal / 50; }
	uint32_t GetGrainCount() { return mGrainCounter; }

	Player &GetPlayer() { return *mPlayer; }

private:
	DrawManager mDrawManager;
	WindowManager mWindowManager;
	LogicManager mLogicManager;
	MapManager mMapManager;
	EnemyManager mEnemyManager;

	Player * mPlayer;

	uint32_t mCorpseTotal;
	uint32_t mCorpseCounter;
	uint32_t mGrainCounter;
};

