#pragma once
#include <vector>

#include "EnemyObject.h"

class EnemyManager
{
	friend EnemyObject;
public:
	EnemyManager(uint32_t &aCorpseCounter, uint32_t &aCorpseTotal);
	~EnemyManager();

	bool Update();

	EnemyObject * GetHitEnemy(sf::Vector2f aWorldCoord, float aHeight);

	EnemyObject *GetClosestEnemy(sf::Vector2f aWorldCoord);

protected:
	void Add(EnemyObject &aEnemyObject);

private:
	std::vector<EnemyObject*> mEnemyObjects;

	uint32_t &mCorpseCounter;
	uint32_t &mCorpseTotal;
};

