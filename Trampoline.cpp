#include "pch.h"
#include "Trampoline.h"
#include "Entity.h"
#include "AnimatedSprite.h"


Trampoline::Trampoline( const Point2f& centre, float spriteW, float spriteH, int nrFrames)
	: WorldObjects( centre, spriteW, spriteH, nrFrames)
	, m_JumpHeight { 510.f }
	, m_ExtraJumpHeight { 850.f }
	, m_IsTrampolineActivate { false }
{
	WorldObjects::CreateObject("Trampoline", 225.f, 9);
	m_pSprite->AddAnimation("TrampolineJump", 0.f, 225.f, m_Shape.width, m_Shape.height, 3);
	m_pSprite->SetFramesPerSec(6);
}

#pragma region GeneralFunctions
void Trampoline::Update(float elapsedSec)
{
	WorldObjects::Update(elapsedSec);
}

void Trampoline::ActivateTrampoline(Entity& entity)
{
	m_pSprite->PlayAnimation("TrampolineJump");

	Vector2f newVelocity{ entity.GetVelocity() };

	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	(pStates[SDL_SCANCODE_W])
		? newVelocity.y = m_ExtraJumpHeight
		: newVelocity.y = m_JumpHeight;

	entity.SetVelocity(newVelocity);
}
#pragma endregion 