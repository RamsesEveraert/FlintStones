#include "pch.h"
#include "AnimatedSprite.h"
#include "Texture.h"
#include "Sprite.h"
#include "Vector2f.h"
#include <vector>


AnimatedSprite::AnimatedSprite(const std::string& fileName, float spriteW, float spriteH, float scale, int fps)
	: Sprite(fileName, spriteW, spriteH, scale)
	, m_CurrentFrame{}
	, m_FramesPerSec{ 10 }
	, m_FrameTime{}
	, m_AccumulatedSec{}
	, m_IsCurrentAnimLoop{ true }
	, m_CurrentAnimation{}
	, m_isAnimationDone{ false }
	, m_StopFrame{}
{
	m_SrcRect.bottom = spriteH;
}

#pragma region GeneralFunctions
void AnimatedSprite::Draw() const 
{
	if (m_IsVisible)
	{
		m_pTexture->Draw(m_DestRect, m_SrcRect);
	}
}

void AnimatedSprite::Update(float elapsedSec, const Rectf& shape)
{
	UpdateAnimationFrames(elapsedSec);
	UpdateSpriteSheet();
	UpdateSourceRect();
	UpdateDestinationRect(shape);
}
void AnimatedSprite::UpdateAnimationFrames(float elapsedSec)
{

	if (!m_isAnimationDone)
	{
		m_FrameTime = 1.f / m_FramesPerSec;
		m_AccumulatedSec += elapsedSec;

		if (m_AccumulatedSec > m_FrameTime)
		{
			++m_CurrentFrame;
			m_AccumulatedSec -= m_FrameTime;

			if (m_CurrentFrame >= (m_Cols * m_Rows))
			{
				m_CurrentFrame = m_StopFrame;
				if (!m_IsCurrentAnimLoop)
				{
					m_isAnimationDone = true;
				}

			}

		}
	}

}
void AnimatedSprite::UpdateSourceRect()
{
	m_SrcRect.left = m_SpriteSheet.left + m_CurrentFrame % m_Cols * m_SrcRect.width;
	m_SrcRect.bottom = m_SpriteSheet.bottom + (m_CurrentFrame / m_Cols + 1) * m_SrcRect.height;

}
void AnimatedSprite::UpdateDestinationRect(const Rectf& shape)
{
	m_DestRect.left = shape.left;
	m_DestRect.bottom = shape.bottom;
}
void AnimatedSprite::UpdateSpriteSheet()
{
	if (m_Animation.find(m_CurrentAnimation) != m_Animation.end())
	{
		m_SpriteSheet = m_Animation[m_CurrentAnimation];
	}

}

void AnimatedSprite::PlayAnimation(const std::string& animation, int stopFrame, bool isLoop)
{
	m_Cols = int(m_Animation[animation].width / m_SpriteW);

	m_IsCurrentAnimLoop = isLoop;
	m_StopFrame = stopFrame;

	if (m_CurrentAnimation != animation)
	{
		m_isAnimationDone = false;
		m_CurrentAnimation = animation;
		m_CurrentFrame = 0;
	}
}
void AnimatedSprite::AddAnimation(const std::string& name, float left, float bottom, float spriteW, float spriteH, int frames)
{
	Rectf animationSheet{ left, bottom, spriteW * frames, spriteH };

	if (!m_Animation.insert(std::make_pair(name, animationSheet)).second)
	{
		std::cout << "ERROR insertion of: " << name << std::endl;
	}
}
void AnimatedSprite::StopAnimation()
{
	m_CurrentFrame = 0;
	m_isAnimationDone = true;
}

void AnimatedSprite::RotateSprite(float angleDeg, float x, float y, float z)
{
	glPushMatrix();
	glTranslatef(m_DestRect.left + (m_DestRect.width / 2), m_DestRect.bottom + (m_DestRect.height / 2), 0.f);
	glRotatef(angleDeg, x, y, z);
	glTranslatef(-(m_DestRect.left + (m_DestRect.width / 2)), -(m_DestRect.bottom + (m_DestRect.height / 2)), 0.f);
	glPopMatrix();
}
#pragma endregion 
#pragma region GettersAndSetters
bool AnimatedSprite::IsVisible()
{
	return m_IsVisible;
}
void AnimatedSprite::SetVisible(bool isVisible)
{
	m_IsVisible = isVisible;
}
void AnimatedSprite::SetScale(float scale)
{
	m_Scale = scale;
}
void AnimatedSprite::SetFramesPerSec(int fps)
{
	m_FramesPerSec = fps;
}
#pragma endregion 












