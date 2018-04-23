#include "EnemyManager.h"

EnemyManager::EnemyManager(uint32_t &aCorpseCounter, uint32_t &aCorpseTotal) :
	mCorpseCounter(aCorpseCounter),
	mCorpseTotal(aCorpseTotal)
{
}

EnemyManager::~EnemyManager()
{
}

bool EnemyManager::Update()
{
	for (EnemyObject *&eo : mEnemyObjects)
	{
		if (eo->isDead())
		{
			eo = NULL;
		}
	}
	mEnemyObjects.erase(std::remove(mEnemyObjects.begin(), mEnemyObjects.end(), reinterpret_cast<EnemyObject*>(NULL)), mEnemyObjects.end());

	for (int i = 0; i < mEnemyObjects.size(); i++)
	{
		for (int j = i + 1; j < mEnemyObjects.size(); j++)
		{
			EnemyObject *e1, *e2;
			float hr1, hr2;
			e1 = mEnemyObjects[i];
			e2 = mEnemyObjects[j];
			hr1 = sqrt(e1->GetHitRadiusSquared());
			hr2 = sqrt(e2->GetHitRadiusSquared());

			float dist = e1->DistanceTo(e2->GetWorldCoords());
			if (dist < hr1 + hr2)
			{
				if (e1->GetMass() > e2->GetMass())
				{
					EnemyObject *temp;
					temp = e1; e1 = e2; e2 = temp;
				}
				float forceDist = hr1 + hr2 - dist;
				sf::Vector2f displacement = (e1->GetWorldCoords() - e2->GetWorldCoords());
				displacement *= forceDist / dist;

				e1->ForceMove(displacement);
			}
		}
	}
	return true;
}

EnemyObject *EnemyManager::GetHitEnemy(sf::Vector2f aWorldCoord, float aHeight)
{
	for (EnemyObject *&eo : mEnemyObjects)
	{
		if (aHeight > eo->GetHeight())
			continue;
		float hrs = eo->GetHitRadiusSquared();
		if (eo->DistanceSquaredTo(aWorldCoord) < hrs)
			return eo;
	}
	return NULL;
}

EnemyObject *EnemyManager::GetClosestEnemy(sf::Vector2f aWorldCoord)
{
	EnemyObject *rval = NULL;
	float curDist = 0.f;

	for (EnemyObject *eo : mEnemyObjects)
	{
		if (eo == NULL || eo->isDead()) continue;
		if (rval == NULL)
		{
			rval = eo;
			curDist = eo->DistanceTo(aWorldCoord);
		}
		else
		{
			if (eo->DistanceTo(aWorldCoord) < curDist)
			{
				rval = eo;
				curDist = eo->DistanceTo(aWorldCoord);
			}
		}
	}

	return rval;
}

void EnemyManager::Add(EnemyObject & aEnemyObject)
{
	mEnemyObjects.push_back(&aEnemyObject);
}
