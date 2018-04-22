#include "MapManager.h"

#include <assert.h>


MapManager::MapManager() :
	mTiles(),
	mDummyTile()
{
	mDummyTile.mSmellFactor = 0;
	mDummyTile.mLastTouched = 0;
}


MapManager::~MapManager()
{
}

bool MapManager::Update()
{
	return true;
}

Tile &MapManager::GetTile(sf::Vector2<uint32_t> aTileCoord)
{
	if (aTileCoord.x >= kMaxX || aTileCoord.y >= kMaxY) return mDummyTile;
	return mTiles[aTileCoord.x][aTileCoord.y];
}

sf::Vector2f MapManager::GetTileDrawOrigin(const sf::Vector2<uint32_t> &aTileCoord)
{
	return sf::Vector2f(((int32_t) aTileCoord.x - (int32_t) aTileCoord.y) * kTileWidth,
	                            (aTileCoord.x + aTileCoord.y) * kTileHeight);
}

sf::Vector2f MapManager::GetTileDrawCenter(const sf::Vector2<uint32_t> &aTileCoord)
{
	sf::Vector2f rval = GetTileDrawOrigin(aTileCoord);

	rval.x += (kTileHeight / 2);

	return rval;
}

sf::Vector2i MapManager::GetTileCoords(sf::Vector2f aWorldCoords)
{
	int32_t div = MapManager::kTileWidth + (2 * MapManager::kTileHeight);
	int32_t Sy = static_cast<int32_t>(aWorldCoords.y);
	int32_t Sx = static_cast<int32_t>(aWorldCoords.x);

	sf::Vector2i tileCoords(((2 * Sy) + Sx) / div, ((2 * Sy) - Sx) / div);
	tileCoords += {1, 1};

	return tileCoords;
}
