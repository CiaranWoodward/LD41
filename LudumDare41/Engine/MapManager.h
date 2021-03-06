#pragma once

#include <SFML\System.hpp>
#include "TileObject.h"

class Tile
{
public:
	Tile() : mTileObject(NULL) {};

	//Returns true if nothing left to attack (destroyed)
	bool Damage(uint32_t damage) { return (mTileObject == NULL) ? true : mTileObject->Damage(damage); }
	
	int32_t GetBlockFactor() const { return (mTileObject == NULL) ? 0 : mTileObject->GetBlockFactor(); }
	int32_t GetKeenFactor() const { return (mTileObject == NULL) ? 0 : mTileObject->GetKeenFactor(); };

	TileObject *GetTileObject() { return mTileObject; }
	void SetTileObject(TileObject *aTileObject) { mTileObject = aTileObject; }

	void IncrementSmellFactor(uint32_t aSmellFactor)
	{
		mLastTouched += aSmellFactor;
		if ((mSmellFactor + aSmellFactor) < mSmellFactor) mSmellFactor = UINT32_MAX;
		else mSmellFactor += aSmellFactor;
	}

	uint32_t mSmellFactor;
	uint32_t mLastTouched;

private:
	TileObject *mTileObject;
};

class MapManager
{
public:
	MapManager();
	~MapManager();

	bool Update();

	static const size_t kMaxX = 100;
	static const size_t kMaxY = 100;

	static const int32_t kTileWidth = 26;
	static const int32_t kTileHeight = 13;

	Tile &GetTile(sf::Vector2<uint32_t> aTileCoord);
	static sf::Vector2f GetTileDrawOrigin(const sf::Vector2<uint32_t> &aTileCoord);
	static sf::Vector2f GetTileDrawCenter(const sf::Vector2<uint32_t> &aTileCoord);
	static sf::Vector2i GetTileCoords(sf::Vector2f aWorldCoords);

	static sf::Vector2f GetProjectedCoords(sf::Vector3f a3dPos) { return sf::Vector2f(a3dPos.x, (a3dPos.y / 2) - a3dPos.z); }
	static sf::Vector3f GetFloorCoords(sf::Vector2f aWorldCoords) { return sf::Vector3f(aWorldCoords.x, aWorldCoords.y * 2, 0.f); }

private:
	Tile mTiles[kMaxX][kMaxY];
	Tile mDummyTile;
};

