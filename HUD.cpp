#include "pch.h"
#include "HUD.h"
#include "AnimatedSprite.h"
#include "Texture.h"
#include "Player.h"
#include "Camera.h"

HUD::HUD(const Camera* camera, const Player* player)
	: m_Camera{ camera}
	, m_CameraScale {2.7f}
	, m_PauseTimer {0}
	, m_pPlayer {player}
	, m_MaxHearts {6}
	, m_MinHearts {3}
	, m_Offset{ 20.f }
	, m_Gap{ 3.f }
	, m_PositionHearts{}
	, m_ScoreCount {}
	, m_MaxCoinSprites{2}
	, m_CoinCount {}
	, m_MaxNumbers {7}
	, m_pScoreCountSprite {}
{
	SetupSprites();

	m_ScoreSymbolShape = Rectf{
								m_Offset ,
								m_Camera->GetCamera().height / m_CameraScale - m_Offset ,
								m_pScoreSymbol->GetSpriteWidth(),
								m_pScoreSymbol->GetSpriteHeight()
							};

	m_CoinSymbolShape = Rectf{ 
								(m_Camera->GetCamera().width / m_CameraScale) - 3 * m_Offset,
								(m_Camera->GetCamera().height / m_CameraScale) - m_Offset - m_ScoreSymbolShape.height ,
								 m_pCoinSymbol->GetSpriteWidth(),
								 m_pCoinSymbol->GetSpriteHeight()
	};

	m_LiveSymbolShape = m_PosLives = Rectf{
											(m_Camera->GetCamera().width / m_CameraScale) - 3 * m_Offset,
											m_Offset,
											m_pLivesSymbol->GetSpriteWidth(),
											m_pLivesSymbol->GetSpriteHeight()
	};

	m_PosLives.left = m_LiveSymbolShape.left + m_LiveSymbolShape.width + m_Gap;

	m_PosPause = Rectf{
						((m_Camera->GetCamera().width / m_CameraScale) / 2) - (m_pPause->GetSpriteWidth() / 2),
						((m_Camera->GetCamera().height / m_CameraScale) / 2) - (m_pPause->GetSpriteHeight() / 2),
						 m_pPause->GetSpriteWidth(),
						 m_pPause->GetSpriteHeight()	
	};

}

HUD::~HUD()
{
	HUD::DeleteSprites();
}

void HUD::Draw(bool isPaused) const
{
	glPushMatrix();
		glScalef(2.7f, 2.7f, 1.f);

		if (isPaused)
		{
			m_pPause->Draw();
		}

		DrawHearts();
		DrawCounter(m_pScoreSymbol, m_pScoreCountSprite, m_ScoreCount);
		DrawCounter(m_pCoinSymbol, m_pCoinCountSprite, m_CoinCount);
		DrawCounter(m_pLivesSymbol, m_pLivesCountSprite, m_LivesCount);
	glPopMatrix();
	
}


void HUD::Update(float elapsedSec)
{		
		UpdateHearts(elapsedSec);
		UpdateCoins(elapsedSec);
		UpdateScore(elapsedSec);
		UpdateLives(elapsedSec);
	
}

void HUD::ResetPauseTimer()
{
	m_PauseTimer = 0;
	m_pPause->SetVisible(true);
}

void HUD::SetupSprites()
{

	// hearts

	Rectf posHearts{};
	Vector2f sizeHeart{ 13.f,11.f };

		for (size_t idx{ 0 }; idx < m_MaxHearts; ++idx)
		{
			m_pHearts.push_back(new AnimatedSprite("Resources/Interfaces/HudObjects.png", sizeHeart.x, sizeHeart.y));

		posHearts = Rectf{0.f,0.f,13.f,11.f};
		int offset{ 2 };

		m_PositionHearts.push_back(posHearts);

		m_pHearts[idx]->AddAnimation("FullHaert", 0.f, 0.f, sizeHeart.x, sizeHeart.y, 1);
		m_pHearts[idx]->AddAnimation("EmptyHeart", offset * sizeHeart.x, 0.f, sizeHeart.x, sizeHeart.y, 1);
		m_pHearts[idx]->PlayAnimation("FullHaert");
	}

	// score

	Vector2f sizeScore{ 40.f,8.f };
	m_pScoreSymbol = new AnimatedSprite("Resources/Interfaces/Score.png", sizeScore.x, sizeScore.y);

	SetupCountTexture(m_MaxNumbers, m_pScoreCountSprite);

	// coins 

	float sizeCoinSymbol{ 16.f };
	m_pCoinSymbol = new AnimatedSprite("Resources/Interfaces/HudObjects.png", sizeCoinSymbol, sizeCoinSymbol);
	m_pCoinSymbol->AddAnimation("Coin", sizeCoinSymbol, sizeHeart.y, sizeCoinSymbol, sizeCoinSymbol, 1);
	m_pCoinSymbol->PlayAnimation("Coin");

	SetupCountTexture(m_MaxCoinSprites, m_pCoinCountSprite);

	// lives

	float sizeLivesSymbol{ 16.f };
	m_pLivesSymbol = new AnimatedSprite("Resources/Interfaces/HudObjects.png", sizeLivesSymbol, sizeLivesSymbol);
	m_pLivesSymbol->AddAnimation("Lives", 0.f, sizeHeart.y, sizeLivesSymbol, sizeLivesSymbol, 1);
	m_pLivesSymbol->PlayAnimation("Lives");

	SetupCountTexture(1, m_pLivesCountSprite);	

	// pause

	Vector2f sizePauseSprite{ 46.f, 12.f };
	m_pPause = new AnimatedSprite("Resources/Interfaces/HudObjects.png", sizePauseSprite.x, sizePauseSprite.y);
	m_pPause->AddAnimation("Pause", 0.f, sizeHeart.y + sizeCoinSymbol, sizePauseSprite.x, sizePauseSprite.y, 1);
	m_pPause->PlayAnimation("Pause")	;	

}


void HUD::DrawHearts() const
{
	

	const int hearts{ m_pPlayer->GetHearts() };

	if (hearts >= m_MinHearts)
	{
		for (size_t idx{ }; idx < hearts; ++idx)
		{
			m_pHearts[idx]->Draw();
			m_pHearts[idx]->PlayAnimation("FullHaert");
		}
	}

	
	else if (hearts < m_MinHearts)
	{
		for (size_t idx{ }; idx < m_MinHearts; ++idx)
		{
			if (hearts > 0)
			{
				(hearts % (idx + 1) == 0)
					? m_pHearts[idx]->PlayAnimation("FullHaert")
					: m_pHearts[idx]->PlayAnimation("EmptyHeart");
			}
			else
			{
				m_pHearts[idx]->PlayAnimation("EmptyHeart");
			}

			m_pHearts[idx]->Draw();
		}
	}

	
}

void HUD::UpdateHearts(float elapsedSec)
{
	for (size_t idx{ 0 }; idx < m_MaxHearts; ++idx)
	{
		m_PositionHearts[idx].left = m_Offset + idx * (m_PositionHearts[idx].width + m_Gap);
		m_PositionHearts[idx].bottom = m_Offset;
		m_pHearts[idx]->Update(elapsedSec, m_PositionHearts[idx]);
	}
}
void HUD::UpdateScore(float elapsedSec)
{
	m_ScoreCount = std::to_string(m_pPlayer->GetScore());

	m_pScoreSymbol->Update(elapsedSec, m_ScoreSymbolShape);

	for (size_t idx{ 0 }; idx < m_ScoreCount.size(); ++idx)
	{
		std::string number{};			// character to string https://stackoverflow.com/questions/17201590/c-convert-from-1-char-to-string
		number = std::string(1, m_ScoreCount[idx]);

		Rectf scorePosition{
									m_Offset + idx * m_pScoreCountSprite[idx]->GetSpriteWidth() ,
									m_Camera->GetCamera().height / m_CameraScale - m_Offset - m_ScoreSymbolShape.height ,
									m_pScoreCountSprite[idx]->GetSpriteWidth(),
									m_pScoreCountSprite[idx]->GetSpriteHeight()
			};


			m_pScoreCountSprite[idx]->PlayAnimation(number);
			m_pScoreCountSprite[idx]->Update(elapsedSec, scorePosition);
	
	}


}
void HUD::UpdateCoins(float elapsedSec)
{
	m_CoinCount = std::to_string(m_pPlayer->GetCoinsCount());

	m_pCoinSymbol->Update(elapsedSec, m_CoinSymbolShape);


	for (size_t idx{}; idx < m_CoinCount.size(); ++idx)
	{
		std::string number{};			// character to string https://stackoverflow.com/questions/17201590/c-convert-from-1-char-to-string
		number = std::string(1, m_CoinCount[idx]);

		m_PosCoinPoints = Rectf{
								m_CoinSymbolShape.left + m_CoinSymbolShape.width + m_Gap + (idx * m_pCoinCountSprite[idx]->GetSpriteHeight()) ,
								(m_Camera->GetCamera().height / m_CameraScale) - m_Offset - m_ScoreSymbolShape.height ,
								m_pCoinCountSprite[idx]->GetSpriteWidth(),
								m_pCoinCountSprite[idx]->GetSpriteHeight()
		};

		m_pCoinCountSprite[idx]->PlayAnimation(number);
		m_pCoinCountSprite[idx]->Update(elapsedSec, m_PosCoinPoints);



	}
}
void HUD::UpdateLives(float elapsedSec)
{
	m_LivesCount = std::to_string( m_pPlayer->GetLives());

	m_pLivesSymbol->Update(elapsedSec, m_LiveSymbolShape);

	m_pLivesCountSprite[0]->PlayAnimation(m_LivesCount);
	m_pLivesCountSprite[0]->Update(elapsedSec, m_PosLives);


}

void HUD::UpdatePause(float elapsedSec)
{
	m_PauseTimer++;

	if (m_PauseTimer >= 30)
	{
		m_PauseTimer = 0;

		(m_pPause->IsVisible())
			? m_pPause->SetVisible(false)
			: m_pPause->SetVisible(true);
	}
	m_pPause->Update(elapsedSec, m_PosPause);
}

void HUD::SetupCountTexture(const int maxElements, std::vector<AnimatedSprite*>& spriteVector)
{
	int maxNumbers{ 10 };
	float numberSize{ 8.f };

	std::string texturePath{ "Resources/Interfaces/scoreNumbers.png" };

	for (size_t idx{}; idx <= maxElements; ++idx)
	{
		spriteVector.push_back(new AnimatedSprite(texturePath, numberSize, numberSize));

		for (size_t number{}; number < maxNumbers; ++number)
		{
			std::string sprite{ std::to_string(number) };
			float leftPos{ number * numberSize };

			spriteVector[idx]->AddAnimation(sprite, leftPos, 0.f, numberSize, numberSize, 1);
		}

		spriteVector[idx]->PlayAnimation("0");
	}
}
void HUD::DrawCounter(const AnimatedSprite* symbol, const std::vector<AnimatedSprite*>& counterSprite, const std::string& score) const
{
	symbol->Draw();

	for (size_t idx{}; idx < score.size(); ++idx)
	{
		counterSprite[idx]->Draw();
	}
}


void HUD::DeleteSprites()
{

	delete m_pPause;
	m_pPause = nullptr;

	for (size_t idx{ 0 }; idx < m_MaxHearts; ++idx)
	{
		delete m_pHearts[idx];
		m_pHearts[idx] = nullptr;
	}

	m_pHearts.clear();
	m_PositionHearts.clear();


	delete m_pScoreSymbol;
	m_pScoreSymbol = nullptr;

	delete m_pCoinSymbol;
	m_pCoinSymbol = nullptr;

	delete m_pLivesSymbol;
	m_pLivesSymbol = nullptr;

	

	for (size_t idx{ 0 }; idx < m_pLivesCountSprite.size(); ++idx)
	{
		delete m_pLivesCountSprite[idx];
		m_pLivesCountSprite[idx] = nullptr;
	}

	for (size_t idx{ 0 }; idx < m_pScoreCountSprite.size(); ++idx)
	{
		delete m_pScoreCountSprite[idx];
		m_pScoreCountSprite[idx] = nullptr;
	}

	for (size_t idx{ 0 }; idx < m_pCoinCountSprite.size(); ++idx)
	{
		delete m_pCoinCountSprite[idx];
		m_pCoinCountSprite[idx] = nullptr;
	}

	m_pScoreCountSprite.clear();
	m_pCoinCountSprite.clear();
	m_pLivesCountSprite.clear();

}
