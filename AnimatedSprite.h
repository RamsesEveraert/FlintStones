#pragma once
#include "Sprite.h"

class AnimatedSprite final : public Sprite
{

public:

	AnimatedSprite(const std::string& fileName, float spriteW, float spriteH, float scale = 1.f, int fps = 10);

	virtual void Update(float elapsedSec, const Rectf& shape) override;
	virtual void Draw() const override;

	void PlayAnimation(const std::string& animation, int stopFrame = 0, bool isLoop = true);
	void AddAnimation(const std::string& name, float left, float bottom, float spriteW, float spriteH, int frames);
	void StopAnimation();
	
	bool IsVisible();
	void SetVisible(bool isVisible);
	void SetScale(float scale);
	void SetFramesPerSec(int fps);

	void RotateSprite(float angleDeg, float x, float y, float z); // voor later

	

private:

	void UpdateAnimationFrames(float elapsedSec);
	void UpdateSourceRect();
	void UpdateDestinationRect(const Rectf& shape);
	void UpdateSpriteSheet();

	std::map<std::string, Rectf > m_Animation;
	std::string m_CurrentAnimation;

	int m_CurrentFrame, m_FramesPerSec, m_StopFrame;
	float m_FrameTime, m_AccumulatedSec;
	bool m_IsCurrentAnimLoop, m_isAnimationDone;



};

