#pragma once

#include <cstdint>
#include <SFML\Graphics.hpp>

class DrawManager;

class DrawObject
{
public:
	DrawObject(DrawManager &aDrawManager, sf::Drawable &aDrawable, int32_t aDrawLevel);
	~DrawObject();

	sf::Drawable &GetSprite() const { return mDrawable; }

	int32_t GetDrawLevel() const { return mDrawLevel; }
	void SetDrawLevel(int32_t aDrawLevel);
	void SetInactive(bool aInactive) { mInactive = aInactive; }
	bool GetInactive() { return mInactive; }

private:
	DrawManager &mDrawManager;

	sf::Drawable &mDrawable;
	int32_t mDrawLevel;
	bool mInactive;
};

