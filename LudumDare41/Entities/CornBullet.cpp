#include "CornBullet.h"
#include "../Engine/EnemyManager.h"
#include "../VectorTools.h"

CornBullet::CornBullet(GameManager & aGameManager, sf::Vector3f aStartPoint, sf::Vector3f aBaseVelocity, sf::Vector3f aDirection) :
	LogicObject(aGameManager.GetLogicManager()),
	mGameManager(aGameManager),
	mSprite(),
	mShadowSprite(),
	mDrawObject(mGameManager.GetDrawManager(), mSprite, 0),
	mShadowDrawObject(mGameManager.GetDrawManager(), mShadowSprite, 0),
	mParticleHelper(aStartPoint, 800.f * aDirection + VectorTools::GetRandomScatter(40.f) + aBaseVelocity, 0.6f, 0.2f, 0.001f),
	mTimeout(sf::seconds(12))
{
	int randOffset = (std::rand() % 4) * 2;

	mSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mSprite.setTextureRect(sf::IntRect(0, 837 + randOffset, 2, 2));
	mSprite.setPosition(MapManager::GetProjectedCoords(aStartPoint));
	mSprite.setOrigin(mSprite.getTextureRect().width / 2.f, mSprite.getTextureRect().height);
	mShadowSprite.setTexture(mGameManager.GetDrawManager().GetGlobalTexture());
	mShadowSprite.setTextureRect(sf::IntRect(0, 845, 2, 2));
	mShadowSprite.setPosition(MapManager::GetProjectedCoords(aStartPoint - sf::Vector3f(0.f, 0.f, aStartPoint.z)));
	mShadowSprite.setOrigin(mShadowSprite.getTextureRect().width / 2.f, mShadowSprite.getTextureRect().height);
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(aStartPoint).y + aStartPoint.z));
	mShadowDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(aStartPoint).y - 1));
}

CornBullet::~CornBullet()
{
}

bool CornBullet::Update(sf::Time dt)
{
	HandleDamage(dt);

	sf::Vector3f newCoords = mParticleHelper.GetNewCoords(dt);
	
	mSprite.setPosition(MapManager::GetProjectedCoords(newCoords));
	mDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(newCoords).y + newCoords.z));

	if (!mParticleHelper.IsDead())
	{
		mShadowSprite.setPosition(MapManager::GetProjectedCoords(newCoords - sf::Vector3f(0.f, 0.f, newCoords.z)));
		mShadowDrawObject.SetDrawLevel(static_cast<int32_t>(MapManager::GetProjectedCoords(newCoords).y - 1));
	}
	else
	{
		mShadowDrawObject.SetDrawLevel(INT_MIN);
		mShadowDrawObject.SetInactive(true);
	}
	mTimeout -= dt;
	if (mTimeout < sf::seconds(2.f))
	{
		mSprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(mTimeout.asSeconds() * 127.f)));
		mShadowSprite.setColor(sf::Color::Transparent);
	}
	if (mTimeout <= sf::Time::Zero)
	{
		return false;
	}

	return true;
}

void CornBullet::HandleDamage(sf::Time dt)
{
	if (mParticleHelper.IsDead()) return;

	sf::Vector3f vel = mParticleHelper.GetVelocity();
	sf::Vector3f pos = mParticleHelper.GetCoords();
	float speed = sqrt(vel.x * vel.x + vel.y * vel.y + vel.z * vel.z);

	EnemyObject *eo = mGameManager.GetEnemyManager().GetHitEnemy(sf::Vector2f(pos.x, pos.y / 2), pos.z);
	if (eo == NULL) return;

	float damage = speed * 0.01f;
	//TODO: Vector arithmetic to find collision point... maybe
	if (eo->EvalDamage(damage, pos) < 0.02f)
	{
		mParticleHelper.vertBounce();
	}
	else
	{
		eo->Damage(damage, pos, vel);
		mTimeout = sf::Time::Zero;
	}
}
