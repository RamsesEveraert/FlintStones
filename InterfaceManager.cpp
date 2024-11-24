#include "pch.h"
#include "InterfaceManager.h"
#include "AnimatedSprite.h"
#include "Player.h"
#include "Texture.h"
#include "Background.h"

InterfaceManager::InterfaceManager(Player* player, float screenWidth, float screenHeight)
	: m_pPlayer {player}
	, m_ScreenWidth {screenWidth}
	, m_ScreenHeight {screenHeight}
	, m_FlashFrames {}
	, m_GameScale {2.7f}
	, m_Background {0.f,0.f,screenWidth,screenHeight}
	, m_Option{ OptionButton::start }
	, m_CurrentScreenState {GameScreenState::titlescreen_phase1 }
	, m_IsRestartActivated { false }
	, m_IsGameStarted { false }
{
	SetupSprites();
}

InterfaceManager::~InterfaceManager()
{
	DeleteSprites();
	
}

void InterfaceManager::DrawTitleScreen() const
{
	TitleScreenBg->Draw();
	
	if (m_CurrentScreenState != GameScreenState::configuration)
	{
		m_TitleScreenText->Draw();
	}

	switch (m_CurrentScreenState)
	{
		case GameScreenState::titlescreen_phase1:
			m_pPressStart->Draw();
			break;
		case GameScreenState::titlescreen_phase2:
			m_StartButton->Draw();
			m_OptionButton->Draw();

			m_SelectionButton1->Draw();
			m_SelectionButton2->Draw();

			break;
	}
}

bool InterfaceManager::GetIsRestartActivated() const
{
	return m_IsRestartActivated;
}

bool InterfaceManager::GetIsGameStarted() const
{
	return m_IsGameStarted;
}

void InterfaceManager::SetGameScreenState(GameScreenState state)
{
	m_CurrentScreenState = state;
}


void InterfaceManager::DrawGameOverScreen() const
{
	m_GameOverScreen->Draw();
	m_pGameOverAnimation->Draw();
	m_pTextureGameOver->Draw(m_DstGameOverText);

	m_SelectionButton1->Draw();
	m_SelectionButton2->Draw();
}


void InterfaceManager::Update(float elapsedSec)
{

	UpdateOptionButton(elapsedSec);
	UpdatePressToStart(elapsedSec);

	glPushMatrix();
		glScalef(m_GameScale, m_GameScale, 1.f);
		UpdateTitleParallax(elapsedSec);
		m_pGameOverAnimation->Update(elapsedSec, m_ShapeGameOverAnimation);
	glPopMatrix();
}

void InterfaceManager::HandleInputs(const SDL_KeyboardEvent& e)
{

	switch (m_CurrentScreenState)
	{
	case GameScreenState::gameover:
		if (e.keysym.sym == SDLK_UP && m_Option != OptionButton::start)
		{
			m_Option = OptionButton::start;
		}
		else if (e.keysym.sym == SDLK_DOWN && m_Option != OptionButton::exit)
		{
			m_Option = OptionButton::exit;
		}
		else if (e.keysym.sym == SDLK_KP_ENTER || e.keysym.sym == SDLK_RETURN)
		{
			
			m_pPlayer->SetLives(0);
			m_pPlayer->SetHearts(3);
			
			if (m_Option == OptionButton::start)
			{
				m_CurrentScreenState = GameScreenState::none;
				m_pPlayer->SetGameOver(false);
			}
			else
			{
				std::cout << "exit activated \n";
				m_IsRestartActivated = true;
				m_CurrentScreenState = GameScreenState::titlescreen_phase1;
			}
		}
		break;
	case GameScreenState::titlescreen_phase1:
		if (e.keysym.sym == SDLK_KP_ENTER || e.keysym.sym == SDLK_RETURN)
		{
			m_CurrentScreenState = GameScreenState::titlescreen_phase2;
		}
		break;
	case GameScreenState::titlescreen_phase2:
		if (e.keysym.sym == SDLK_UP && m_Option != OptionButton::start)
		{
			m_Option = OptionButton::start;
		}
		else if (e.keysym.sym == SDLK_DOWN && m_Option != OptionButton::options)
		{
			m_Option = OptionButton::options;
		}
		else if (e.keysym.sym == SDLK_KP_ENTER || e.keysym.sym == SDLK_RETURN)
		{
			if (m_Option == OptionButton::start)
			{
				m_IsRestartActivated = true; 
				m_IsGameStarted = true;
			}
			else
			{
				//TODO optionsscreen
			}
		}		
		break;
	}

	
}

void InterfaceManager::UpdatePressToStart(float elapsedSec)
{
	m_FlashFrames++;
	if (m_FlashFrames >= 30)
	{
		m_FlashFrames = 0;

		(m_pPressStart->IsVisible())
			? m_pPressStart->SetVisible(false)
			: m_pPressStart->SetVisible(true);
	}

	
	m_pPressStart->Update(elapsedSec, m_PositionPressStat);

}

void InterfaceManager::UpdateOptionButton(float elapsedSec)
{
	switch (m_Option)
	{
	case OptionButton::none:
	case OptionButton::start:
		m_SelectionButton1->SetVisible(true);
		m_SelectionButton2->SetVisible(false);
		break;
	case OptionButton::exit:
	case OptionButton::options:
		m_SelectionButton1->SetVisible(false);
		m_SelectionButton2->SetVisible(true);
		break;
	}

	m_SelectionButton1->Update(elapsedSec, m_PosSelectionButton1);
	m_SelectionButton2->Update(elapsedSec, m_PosSelectionButton2);

	m_StartButton->Update(elapsedSec, m_posStartButton);
	m_OptionButton->Update(elapsedSec, m_posOptionButton);


}

void InterfaceManager::UpdateTitleParallax(float elapsedSec)
{
	TitleScreenBg->LoopBackground(elapsedSec, false);
}

void InterfaceManager::SetupSprites()
{
	const float margin{ 65.f };
	const float textScale{ 2.2f };
	const float offsetCenter{ 40.f };
	const float buttonOffset{ 12.f };


	m_GameOverScreen = new Texture("Resources/Interfaces/Game_Over/GameOverScreen.png");

	m_pGameOverAnimation = new AnimatedSprite("Resources/Interfaces/Game_Over/GameOverFred.png", 50.f, 40.f, m_GameScale);
	m_pGameOverAnimation->AddAnimation("GameOver", 0.f, 0.f, 50.f, 40.f, 3);
	m_pGameOverAnimation->PlayAnimation("GameOver");

	m_ShapeGameOverAnimation = Rectf{
									  (m_ScreenWidth / 2) - (m_pGameOverAnimation->GetSpriteWidth() / 2) - offsetCenter,
									  (m_ScreenHeight / 2) - (m_pGameOverAnimation->GetSpriteHeight() / 2),
									  m_pGameOverAnimation->GetSpriteWidth(),
									  m_pGameOverAnimation->GetSpriteHeight()
									};

	m_pTextureGameOver = new Texture("Resources/Interfaces/Game_Over/GameOverText.png");

	m_DstGameOverText = Rectf{
										margin,
										m_ScreenHeight - margin - (m_pTextureGameOver->GetHeight() * textScale),
										m_pTextureGameOver->GetWidth() * textScale,
										m_pTextureGameOver->GetHeight() * textScale
									};

	m_SelectionButton1 = new AnimatedSprite("Resources/Interfaces/SelectionButton.png", 7.f, 6.f, m_GameScale);
	m_SelectionButton2 = new AnimatedSprite("Resources/Interfaces/SelectionButton.png", 7.f, 6.f, m_GameScale);

	m_PosSelectionButton1 = m_PosSelectionButton2 = Rectf{
														 (m_ScreenWidth / 2) - (m_pGameOverAnimation->GetSpriteWidth() / 2) - 2 * (offsetCenter + m_SelectionButton1->GetSpriteWidth()),
														 (m_ScreenHeight / 2) - (m_pGameOverAnimation->GetSpriteHeight() / 2) - offsetCenter + m_SelectionButton1->GetSpriteHeight() + buttonOffset,
														  m_SelectionButton1->GetSpriteWidth(),
														  m_SelectionButton1->GetSpriteHeight()
	};

	m_PosSelectionButton2.bottom = m_PosSelectionButton1.bottom - offsetCenter;

	const Rectf Viewport{ m_Background };
	TitleScreenBg = new Background(Viewport, true);

	m_TitleScreenText = new Texture("Resources/Interfaces/TitleScreen/TitleScreenText.png");
	m_pPressStart = new AnimatedSprite("Resources/Interfaces/TitleScreen/PressStartButton.png",333.f, 24.f);
	m_PositionPressStat = Rectf{ 
								m_ScreenWidth / 2 - m_pPressStart->GetSpriteWidth() / 2, 
								m_ScreenHeight / 2 - 2 * m_pPressStart->GetSpriteHeight(),
								m_pPressStart->GetSpriteWidth(),
								m_pPressStart ->GetSpriteHeight()
								
	};

	m_StartButton = new AnimatedSprite("Resources/Interfaces/TitleScreen/StartButton.png", 92.f, 22.f);
	m_posStartButton = Rectf{
								m_ScreenWidth / 2 - m_StartButton->GetSpriteWidth() / 2,
								m_ScreenHeight / 2 - 2 * m_StartButton->GetSpriteHeight(),
								m_StartButton->GetSpriteWidth(),
								m_StartButton->GetSpriteHeight()

	};

	m_OptionButton = new AnimatedSprite("Resources/Interfaces/TitleScreen/OptionButton.png", 112.f, 22.f);
	m_posOptionButton = Rectf{
								m_ScreenWidth / 2 - m_OptionButton->GetSpriteWidth() / 2,
								m_posStartButton.bottom - 2 * m_OptionButton->GetSpriteHeight(),
								m_OptionButton->GetSpriteWidth(),
								m_OptionButton->GetSpriteHeight()

	};
}

void InterfaceManager::DeleteSprites()
{
	delete m_GameOverScreen;
	m_GameOverScreen = nullptr;

	delete m_pGameOverAnimation;
	m_pGameOverAnimation = nullptr;

	delete m_pTextureGameOver;
	m_pTextureGameOver = nullptr;

	delete m_SelectionButton1;
	m_SelectionButton1 = nullptr;

	delete m_SelectionButton2;
	m_SelectionButton2 = nullptr;

	delete TitleScreenBg;
	TitleScreenBg = nullptr;

	delete m_TitleScreenText;
	m_TitleScreenText = nullptr;

	delete m_pPressStart;
	m_pPressStart = nullptr;

	delete m_StartButton;
	m_StartButton = nullptr;

	delete m_OptionButton;
	m_OptionButton = nullptr;

}
