#pragma once
#include <map>

class AnimatedSprite;
class Entity;

class Effects final 
{
public:
	Effects();
	~Effects();

	Effects(const Effects& other) = delete;
	Effects& operator=(const Effects& other) = delete;
	Effects(Effects&& other) = delete;
	Effects& operator=(Effects&& other) = delete;

	enum class Effect
	{
		charging,
		stunned,
		start_transform,
		end_transform,
		hit
	};

	void Draw() const;
	void Update(float elapsedSec, const Entity& entity);

	void SetDestinationEffect(const Rectf dstRectCenter);
	void SetDuration(float duration);
	void SetEffectOffset(const Point2f& offset);

	void PlayEffect(Effect effect, bool isLoop, float startTime, float duration = -1, int fps = 6);
	void StopEffect();

	const std::string GetCurrentEffectName() const;

private:

	void SetupEffects();
	void HandleEffects(const Entity& entity);

	void ResetVisibility();

	const std::map<std::string, AnimatedSprite* > GetEffects() const;

	Effect m_CurrentEffect;
	std::map<std::string, AnimatedSprite* > m_pEffects;
	AnimatedSprite* m_TransformEffect, *m_StunEffect, *m_ChargeEffect, *m_HitEffect;
	Rectf m_DstRect;

	std::string m_CurrentEffectName;

	int m_Fps;

	Point2f m_EffectOffset;

	float m_startTimer, m_TimeToStart, m_AnimationTimer, m_Duration;
	bool m_IsEffectInLoop, m_IsActive;
	
};

