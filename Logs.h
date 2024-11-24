#pragma once

class AnimatedSprite;

class Logs final
{
public:
	Logs(const Rectf& shape, float speed);

	Logs(const Logs& other) = delete;
	Logs& operator=(const Logs& other) = delete;
	Logs(Logs&& other) = delete;
	Logs& operator=(Logs&& other) = delete;

	~Logs();

	void Update(float elapsedSec);
	void Draw() const;

	Rectf GetShape() const;
	Vector2f GetVelocity() const;

private:

	void SetupAnimation() const;
	void MovingLogs(float elapsedSec);

	AnimatedSprite* m_Log;
	Rectf m_Shape;
	Vector2f m_Velocity;

};

