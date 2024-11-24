#include "pch.h"
#include "Effects.h"
#include "AnimatedSprite.h"
#include "Entity.h"

Effects::Effects()
	: m_DstRect {}
	, m_Fps {}
	, m_EffectOffset {}
	, m_startTimer {}
	, m_AnimationTimer{}
	, m_Duration{}
	, m_CurrentEffectName { "Charging"}
	, m_TimeToStart {}
	, m_IsEffectInLoop {}
	, m_IsActive {}
	, m_CurrentEffect {Effect::charging}
{
	Effects::SetupEffects();
	Effects::ResetVisibility();	
}

Effects::~Effects()
{

	std::map<std::string, AnimatedSprite*>::iterator it = m_pEffects.begin();

	while (it != m_pEffects.end())
	{
		delete it->second;
		it->second = nullptr;
		it++;
	}
	m_pEffects.clear();
}

#pragma region Initialization
void Effects::SetupEffects()
{
	m_pEffects.insert(std::make_pair("Hit", new AnimatedSprite("Resources/effects/Effects.png", 50.f, 50.f))).second;
	m_pEffects.insert(std::make_pair("Charging", new AnimatedSprite("Resources/effects/Effects.png", 31.f, 31.f))).second;
	m_pEffects.insert(std::make_pair("Stun", new AnimatedSprite("Resources/effects/Effects.png", 26.f, 18.f))).second;
	m_pEffects.insert(std::make_pair("Transform", new AnimatedSprite("Resources/effects/Effects.png", 50.f, 50.f))).second;

	m_pEffects["Hit"]->AddAnimation("POW", 0.f, 0.f, 50.f, 50.f, 1);
	m_pEffects["Transform"]->AddAnimation("TransformStart", 0.f, 50.f, 50.f, 50.f, 3);
	m_pEffects["Transform"]->AddAnimation("TransformEnd", 0.f, 100.f, 50.f, 50.f, 3);
	m_pEffects["Charging"]->AddAnimation("Charging", 0.f, 150.f, 31.f, 31.f, 3);
	m_pEffects["Stun"]->AddAnimation("Stunned", 0.f, 181.f, 26.f, 18.f, 3);
}
void Effects::ResetVisibility()
{
	std::map<std::string, AnimatedSprite*>::iterator it = m_pEffects.begin();

	while (it != m_pEffects.end())
	{
		it->second->SetVisible(false);
		it++;
	}
}
#pragma endregion 
#pragma region GeneralFunctions
void Effects::Draw() const
{
	Effects::GetEffects().at(m_CurrentEffectName)->Draw();
}

void Effects::Update(float elapsedSec, const Entity& entity)
{
	std::map<std::string, AnimatedSprite*>::iterator it = m_pEffects.begin();

	while (it != m_pEffects.end())
	{
		it->second->Update(elapsedSec, m_DstRect);
		it++;
	}

	if (m_IsActive)
	{
		Effects::HandleEffects(entity);
		m_startTimer += elapsedSec;

		m_pEffects[m_CurrentEffectName]->SetFramesPerSec(m_Fps);

		if (m_startTimer >= m_TimeToStart)
		{
			m_AnimationTimer += elapsedSec;
			m_pEffects[m_CurrentEffectName]->SetVisible(true);
			if (!m_IsEffectInLoop && m_AnimationTimer >= m_Duration)
			{
				Effects::StopEffect();
				m_startTimer = 0;
			}
		}
	}


}

void Effects::HandleEffects(const Entity& entity)
{
	const Rectf entityShape{ entity.GetShape()};
	const bool facingLeft{ entity.IsFacingLeft() };

	switch (m_CurrentEffect)
	{
	case Effect::charging:

		m_DstRect.left = facingLeft ? entityShape.left + 0.4f * entityShape.width + m_EffectOffset.x: entityShape.left;
		m_DstRect.bottom = entityShape.bottom + 0.5f * entityShape.height + m_EffectOffset.y;
		m_DstRect.width = m_DstRect.height = 31.f;

		m_pEffects["Charging"]->PlayAnimation("Charging");
		m_CurrentEffectName = "Charging";
		break;
	case Effect::hit:
		m_pEffects["Hit"]->PlayAnimation("POW");
		m_CurrentEffectName = "Hit";
		break;
	case Effect::stunned:
		m_pEffects["Stun"]->PlayAnimation("Stunned");
		m_CurrentEffectName = "Stun";
		break;
	case Effect::end_transform:
		m_pEffects["Transform"]->PlayAnimation("TransformEnd");
		m_CurrentEffectName = "Transform";
		break;
	case Effect::start_transform:
		m_pEffects["Transform"]->PlayAnimation("TransformStart");
		m_CurrentEffectName = "Transform";
		break;
	}
}
void Effects::PlayEffect(Effect effect, bool isLoop, float startTime, float duration, int fps)
{
	m_CurrentEffect = effect;
	m_TimeToStart = startTime;
	m_IsEffectInLoop = isLoop;
	m_Duration = duration;
	m_Fps = fps;
	m_IsActive = true;
}
void Effects::StopEffect()
{
	m_IsActive = false;
	Effects::ResetVisibility();
	m_startTimer = 0;
	m_AnimationTimer = 0;
}
#pragma endregion 
#pragma region GettersAndSetters
void Effects::SetDestinationEffect(const Rectf dstRect)
{
	m_DstRect = dstRect;
	m_DstRect.left = dstRect.left - m_pEffects[m_CurrentEffectName]->GetSpriteWidth() / 2;
	m_DstRect.bottom = dstRect.bottom - m_pEffects[m_CurrentEffectName]->GetSpriteHeight() / 2;
}
void Effects::SetDuration(float duration)
{
	m_Duration = duration;
}
void Effects::SetEffectOffset(const Point2f& offset)
{
	m_EffectOffset = offset;
}
const std::string Effects::GetCurrentEffectName() const
{
	return m_CurrentEffectName;
}
const std::map<std::string, AnimatedSprite*> Effects::GetEffects() const
{
	return m_pEffects;
}
#pragma endregion 