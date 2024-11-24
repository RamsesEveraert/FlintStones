#include "pch.h"
#include "Background.h"
#include "Texture.h"
#include <string>

Background::Background(const Rectf& cam, bool isTitleScreen)
	: m_pBackgroundElements{}
	, m_AmountBackgrounds {2}
	, m_Camera{ cam }
	, m_BgOffset{-70.f, 150.f}
	, m_IsParallaxActive {false}
	, m_IsTitleScreen {isTitleScreen}
	
{
	m_IsTitleScreen
		? m_Background = cam
		: m_Background = Rectf{ m_Camera.left + m_BgOffset.x, m_Camera.bottom + m_BgOffset.y ,m_Camera.width, m_Camera.height };

	CreateClouds();
	CreateBackground();
	CreateSea();
	InitBgPositions();
}

Background::~Background()
{
	DeleteBackground();
	DeleteClouds();
	DeleteSea();
}

#pragma region Initialization
void Background::CreateBackground()
{
	std::string filePath{ "Resources/Backgrounds/Background.png" };

	m_pBlueBackground = new Texture(filePath);

	filePath = "Resources/Backgrounds/Mountains.png";

	m_pBackgroundElements.push_back(new Texture(filePath));
	m_BgSpeed.push_back(20.f);
	m_BgSpeed.push_back(20.f);

	filePath = "Resources/Backgrounds/Forrest.png";

	m_pBackgroundElements.push_back(new Texture(filePath));
	m_BgSpeed.push_back(50.f);
	m_BgSpeed.push_back(50.f);
}
void Background::CreateClouds()
{
	std::string filePath{ "Resources/Backgrounds/Clouds.png" };

	m_pClouds.push_back(new Texture(filePath));
	m_pClouds.push_back(new Texture(filePath));
}
void Background::CreateSea()
{
	std::string filePath{ "Resources/Backgrounds/Sea.png" };
	m_pSea.push_back(new Texture(filePath));
	m_pSea.push_back(new Texture(filePath));
}
void Background::InitBgPositions()
{
	for (size_t index{}; index < m_pBackgroundElements.size(); ++index)
	{
		m_DestRectBg.push_back(Rectf{ m_Background.left, m_Background.bottom, m_Background.width, m_Background.height });
		m_DestRectBg.push_back(Rectf{ m_Background.left + m_Camera.width, m_Background.bottom, m_Background.width, m_Background.height });
	}
	for (size_t index{}; index < m_pClouds.size(); ++index)
	{
		m_DestRectCloud.push_back(Rectf{ m_Background.left, m_Background.bottom - m_BgOffset.y / 2, m_Background.width, m_Background.height });
		m_DestRectCloud.push_back(Rectf{ m_Background.left - m_Camera.width, m_Background.bottom - m_BgOffset.y / 2, m_Background.width, m_Background.height });
	}
	for (size_t index{}; index < m_pSea.size(); ++index)
	{
		m_DestRectSea.push_back(Rectf{ -20, 0 + index * 50.f, 800.f, 800.f });
	}
}
#pragma endregion 
#pragma region GeneralFunctions
void Background::Draw() const
{
	DrawBackgrounds();
	DrawClouds();

	if (!m_IsTitleScreen)
	{
		DrawSea();
	}
	
}
void Background::DrawBackgrounds() const
{

	m_pBlueBackground->Draw();

	for (size_t index{}; index < m_pBackgroundElements.size(); ++index)
	{
		if (m_pBackgroundElements[index])
		{
			m_pBackgroundElements[index]->Draw(m_DestRectBg[index * 2]);
			m_pBackgroundElements[index]->Draw(m_DestRectBg[index * 2 + 1]);
		}
	}
}
void Background::DrawClouds() const
{
	for (size_t index{}; index < m_pClouds.size(); ++index)
	{
		if(m_pClouds[index]) m_pClouds[index]->Draw(m_DestRectCloud[index]);
	}
}
void Background::DrawSea() const
{
	for (size_t index{}; index < m_pSea.size(); ++index)
	{
		if(m_pSea[index]) m_pSea[index]->Draw(m_DestRectSea[index]);
	}
}

void Background::LoopBackground(float elapsedSec, bool isFacingLeft)
{
	float scaler{ isFacingLeft ? 1.f : -1.f };
	float speedMultiplier{ m_IsTitleScreen ? 2.f : 1.f};

	for (size_t index{}; index < m_pBackgroundElements.size(); ++index)
	{
		m_DestRectBg[index * 2].left += scaler * speedMultiplier * (m_BgSpeed[index * 2] * elapsedSec);
		m_DestRectBg[index * 2 + 1].left += scaler * speedMultiplier * (m_BgSpeed[index * 2 + 1] * elapsedSec);

		Rectf& r1{ m_DestRectBg[index * 2] };
		Rectf& r2{ m_DestRectBg[index * 2 + 1] };

		if (r1.left < -m_Camera.width)
		{
			r1.left = m_Camera.width;
		}
		if (r2.left < -m_Camera.width)
		{
			r2.left = m_Camera.width;
		}
	}
}
void Background::UpdateClouds(float elapsedSec)
{
	const float speedClouds{ m_IsParallaxActive ? 40.f : 20.f };
	const float speedClouds2{ m_IsParallaxActive ? 45.f : 25.f };

	Rectf& r1{ m_DestRectCloud[0] };
	Rectf& r2{ m_DestRectCloud[1] };

	r1.left += speedClouds * elapsedSec;
	r2.left += speedClouds2 * elapsedSec;

	if (r1.left > m_Camera.width)
	{
		r1.left = -m_Camera.width;
	}
	if (r2.left > m_Camera.width)
	{
		r2.left = -m_Camera.width;
	}

}
#pragma endregion 
#pragma region GettersAndSetters
void Background::SetBgPosition(float x, float y)
{
	m_Background.left = x;
	m_Background.bottom = y;
}
void Background::SetParallax(bool isActive)
{
	m_IsParallaxActive = isActive;
}
#pragma endregion 
#pragma region CleanUp
void Background::DeleteBackground()
{

	delete m_pBlueBackground;
	m_pBlueBackground = nullptr;

	for (size_t index{}; index < m_pBackgroundElements.size(); ++index)
	{
		if (m_pBackgroundElements[index])
		{
			delete m_pBackgroundElements[index];
			m_pBackgroundElements[index] = nullptr;
		}		
	}

	m_pBackgroundElements.clear();
}
void Background::DeleteClouds()
{
	for (Texture* pCloud : m_pClouds)
	{
		if (pCloud)
		{
			delete pCloud;
			pCloud = nullptr;
		}
	}
}
void Background::DeleteSea()
{
	for (Texture* pSea : m_pSea)
	{
		if (pSea)
		{
			delete pSea;
			pSea = nullptr;
		}
	}
}
#pragma endregion 