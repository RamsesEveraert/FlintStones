#pragma once
#include <map>

class Texture;

class Sprite
{
public:

	Sprite(const std::string& fileName, float spriteW, float spriteH, float scale = 1.f);
	
	Sprite(const Sprite& other) = delete;
	Sprite& operator=(const Sprite& other) = delete;
	Sprite(Sprite&& other) = delete;
	Sprite& operator=(Sprite&& other) = delete;

	virtual ~Sprite();

	virtual void Update(float elapsedSec, const Rectf& playerShape) = 0;
	virtual void Draw() const = 0;

	const float GetSpriteWidth() const;
	const float GetSpriteHeight() const;

	void SetSpriteWidth(float newSize);
	void SetSpriteHeight(float newSize);
	void SetSpriteLeft(float left);
	void SetSpriteBottom(float bottom);

protected:

	Texture* m_pTexture;
	float m_Scale;
	int m_Cols, m_Rows;
	float m_SpriteW, m_SpriteH;
	Rectf m_SrcRect, m_DestRect, m_SpriteSheet;
	bool m_IsVisible;

private:

	void InitDestinationRect();
	void InitSourceRect();
	void DeleteSprite();




};

