#pragma once

class AnimatedSprite;
class Wall final
{
public:

	Wall(const Rectf& shape);
	~Wall();

	Wall(const Wall& other) = delete;
	Wall& operator=(const Wall& other) = delete;
	Wall(Wall&& other) = delete;
	Wall& operator=(Wall&& other) = delete;

	 void Draw() const;
	 void Update(float elapsedSec);

	 const Rectf GetShape() const;

private:
	void InitWall();

	const Rectf m_Shape;
	AnimatedSprite* m_pSprite;
};

