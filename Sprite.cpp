#include "pch.h"
#include "Sprite.h"
#include "Texture.h"
#include <iostream>

Sprite::Sprite(const std::string& fileName, float spriteW, float spriteH, float scale)
	: m_pTexture{ new Texture(fileName) }
	, m_SpriteW{ spriteW }
	, m_SpriteH{ spriteH }
	, m_Cols{ 1 }
	, m_Rows{ 1 }
	, m_Scale{ scale }
	, m_SpriteSheet{ 0,0,spriteW, spriteH }
	, m_SrcRect{}
	, m_DestRect{}
	, m_IsVisible{ true }

{
	InitSourceRect();
	InitDestinationRect();
}

Sprite::~Sprite()
{
	DeleteSprite();
}

#pragma region Initialization
void Sprite::InitDestinationRect()
{
	m_DestRect.width = m_SpriteW * m_Scale;
	m_DestRect.height = m_SpriteH * m_Scale;
}
void Sprite::InitSourceRect()
{
	m_SrcRect.width = m_SpriteW;
	m_SrcRect.height = m_SpriteH;
}
#pragma endregion 
#pragma region GettersAndSetters
const float Sprite::GetSpriteWidth() const
{
	return m_SrcRect.width;
}
const float Sprite::GetSpriteHeight() const
{
	return m_SrcRect.height;
}

void Sprite::SetSpriteWidth(float newSize)
{
	m_SrcRect.width = newSize;
}
void Sprite::SetSpriteHeight(float newSize)
{
	m_SrcRect.height = newSize;
}
void Sprite::SetSpriteLeft(float left)
{
	m_SrcRect.left = left;
}
void Sprite::SetSpriteBottom(float bottom)
{
	m_SrcRect.bottom = bottom;
}
#pragma endregion 
#pragma region CleanUp
void Sprite::DeleteSprite()
{
	delete m_pTexture;
	m_pTexture = nullptr;
}
#pragma endregion 