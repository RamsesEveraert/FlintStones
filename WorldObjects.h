#pragma once

class AnimatedSprite;
class Level;

class WorldObjects
{
public:
	WorldObjects(const Point2f& centre, float spriteW, float spriteH, int nrFrames);
	virtual ~WorldObjects();

	WorldObjects(const WorldObjects& other) = delete;
	WorldObjects& operator=(const WorldObjects& other) = delete;
	WorldObjects(WorldObjects&& other) = delete;
	WorldObjects& operator=(WorldObjects&& other) = delete;

	void Draw() const;

	virtual void Update(float elapsedSec);
	virtual bool IsOverlapping(const Rectf& rect) const;

	Rectf GetShape() const;


protected:

	void CreateObject(const std::string& animName, float spriteRowBottom, int fps = 10);
	void UpdateObject(float elapsedSec);
	void DeleteObject();

	void SetObjectAnimation(const std::string& animName);
	void AddObjectAnimation(const std::string& animName, float spriteRowBottom, int fps);

	AnimatedSprite* m_pSprite;
	const float m_SpriteWidth, m_SpriteHeight;
	Rectf m_Shape;



	const int m_NrFrames;
	
};

