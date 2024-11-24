#pragma once
#include "Level.h"

class WorldObjects;
class SoundEffect;

class ObjectManager final
{
public:
	ObjectManager();

	ObjectManager(const ObjectManager& other) = delete;
	ObjectManager& operator=(const ObjectManager& other) = delete;
	ObjectManager(ObjectManager&& other) = delete;
	ObjectManager& operator=(ObjectManager&& other) = delete;

	~ObjectManager();

	void Draw() const;
	void Update(float elapsedSec);

	const size_t GetSizeObjects() const;
	const std::vector<WorldObjects*> GetObjects() const;

	//bool HitItem(const Rectf& hitBox, bool isAttacking, Vector2f& velocity, bool isFacingLeft);
	bool HitItem(Entity& entity);

	WorldObjects* CreateRotatingStar(const Point2f& centre, float spriteW, float spriteH, int nrFrames);
	WorldObjects* CreateBalloons(const Point2f& centre, float spriteW, float spriteH, int nrFrames);
	WorldObjects* CreateTrampolines(const Point2f& centre, float spriteW, float spriteH, int nrFrames);
	WorldObjects* CreateEgg(const Point2f& centre, float spriteW, float spriteH, int nrFrames);

private:

	void InitializeObjects();

	void DeleteObject();

	void RemoveObject(size_t index);
	void PopBalloon(std::vector<WorldObjects*> object, size_t index, bool isFacingLeft);

	std::vector<WorldObjects*> m_pObject;

	SoundEffect* m_BalloonPopSound;
	SoundEffect* m_PowerUpSound;
	SoundEffect* m_TrampolineJumpSound;
};