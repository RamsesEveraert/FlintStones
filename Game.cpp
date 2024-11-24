#include "pch.h"
#include "Game.h"
#include "Player.h"
#include "PlayerStateMachine.h"
#include "AnimatedSprite.h"
#include "Level.h"
#include "Camera.h"
#include "FileManager.h"
#include "ObjectManager.h"
#include "EnemyManager.h"
#include "Background.h"
#include "HUD.h"
#include "PlatformBird.h"
#include "InterfaceManager.h"
#include "SoundStream.h"
#include "SoundEffect.h"

Game::Game(const Window& window)
	: m_Window{ window }
	, m_currentGameState { GameState::startscreen }
	, m_GameScale {2.7f}
	, m_IsIntroPlayed { false }
	, m_IsBgMusicPlaying { false }
	, m_IsGameOverMusicPlaying { false }
	, m_IsMusicActivated { true }
	
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}


#pragma region Initialize
void Game::ClearBackground() const
{
	
	glClearColor(0.0f, 0.0f, 0.7f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
void Game::Initialize()
{

	if (m_IsMusicActivated)
	{
		SoundEffect::ToggleAudio(true);
		SoundStream::ToggleAudio(true);
	}
	else
	{
		SoundEffect::ToggleAudio(false);
		SoundStream::ToggleAudio(false);
	}

	m_pObjectManager = new ObjectManager();
	m_pLevel = new Level();
	m_pEnemyManager = new EnemyManager(m_pLevel);
	m_pCamera = new Camera(m_pPlayer, m_Window.width, m_Window.height, m_GameScale);
	m_pCamera->SetLevelBoundaries(m_pLevel->GetBoundaries(), m_pLevel->GetCheckpointWalls());
	m_pBackground = new Background(m_pCamera->GetCamera(), false);
	CreatePlayer();
	m_pHUD = new HUD(m_pCamera, m_pPlayer);
	m_pInterfaceManager = new InterfaceManager(m_pPlayer, m_Window.width, m_Window.height);
	InitializeMainSounds();	



}

void Game::CreatePlayer()
{
	std::string filePath{ "Resources/Player/FredFlintstone.png" };
	Rectf shape{ 140.f, 60.f, 50.f, 50.f };  // original start

	m_pPlayer = new Player(m_pEnemyManager, m_pObjectManager, m_pLevel, filePath, shape, 150.f, 330.f);
}

void Game::InitializeMainSounds()
{
	SoundStream::SetVolume(35);

	m_pIntroMusic = new SoundStream("Resources/Audio/01 - Title Theme.mp3");
	m_pBackgroundMusic = new SoundStream("Resources/Audio/04 - Stage 1 - Let's Rock.mp3");
	m_pGameOverMusic = new SoundStream("Resources/Audio/15 - Game Over.mp3");

	m_PauseSound = new SoundEffect("Resources/Audio/Flintstones_Pause.wav");
	m_PauseSound->SetVolume(60);

	m_pIntroMusic->Play(true);
	m_IsIntroPlayed = true;
}

#pragma endregion
#pragma region GeneralFunctions
void Game::Update(float elapsedSec)
{
	CheckGameState();

	switch (m_currentGameState)
	{
		case GameState::startscreen:
			break;
		case GameState::playing:

			if (m_IsIntroPlayed)
			{
				m_pIntroMusic->FadeOut(700);
				m_IsIntroPlayed = false;
			}

			if (!m_pBackgroundMusic->IsPlaying())
			{
				m_pBackgroundMusic->Play(true);
				m_IsBgMusicPlaying = true;
			}

			m_pBackground->SetParallax(false);
			if (m_pPlayer->GetVelocity().x != 0)
			{
			m_pBackground->SetParallax(true);
			m_pBackground->LoopBackground(elapsedSec, m_pPlayer->IsFacingLeft());
			}

			m_pBackground->UpdateClouds(elapsedSec);
			m_pLevel->Update(elapsedSec);
			m_pPlayer->Update(elapsedSec);
			m_pEnemyManager->Update(elapsedSec, *m_pLevel);
			
			m_pHUD->Update(elapsedSec);

			break;
		case GameState::paused:
			m_pHUD->UpdatePause(elapsedSec);
			m_pPlayer->SetVisible(true);
			break;
		case GameState::game_over:
			if ( m_IsBgMusicPlaying)
			{
				m_pBackgroundMusic->FadeOut(300);
				m_IsBgMusicPlaying = false;
			}
			if (!m_pGameOverMusic->IsPlaying())
			{
				if (!m_IsGameOverMusicPlaying)
				{
					m_pGameOverMusic->Play(false);
				}
				
				m_IsGameOverMusicPlaying = true;
			}
			break;
	}

	m_pInterfaceManager->Update(elapsedSec);

}
	
void Game::Draw() const
{

	bool isPaused{ m_currentGameState == GameState::paused };

	switch (m_currentGameState)
	{
	case GameState::startscreen:

		m_pInterfaceManager->DrawTitleScreen();
		break;

	case GameState::playing:
	case GameState::paused:

		glPushMatrix();
		m_pBackground->Draw();
		glScalef(m_GameScale, m_GameScale, 1.f);
		m_pCamera->Transform(m_pPlayer->GetShape(), m_pPlayer->IsFacingLeft(), m_pPlayer->GetWallsStatus());
		m_pLevel->Draw();
		m_pEnemyManager->Draw(*m_pLevel);
		m_pLevel->DrawForeGround();
		m_pObjectManager->Draw();
		m_pPlayer->Draw(*m_pLevel);
		glPopMatrix();
		m_pHUD->Draw(isPaused);
		break;

	case GameState::game_over:

		m_pInterfaceManager->DrawGameOverScreen();
		m_pInterfaceManager->SetGameScreenState(InterfaceManager::GameScreenState::gameover);
		break;

	}
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{

	switch (e.keysym.sym)
	{
	case SDLK_d:
		break;
	case SDLK_i: // instructions
			ShowGameInstructions();
		break;
	case SDLK_m: //toggle music
		if (m_IsMusicActivated)
		{
			SoundEffect::ToggleAudio(false);
			SoundStream::ToggleAudio(false);
			SoundStream::Stop();
			m_IsMusicActivated = false;
		}
		else
		{
			SoundEffect::ToggleAudio(true);
			SoundStream::ToggleAudio(true);
			m_IsMusicActivated = true;
		}

		break;
	case SDLK_t: // transform test
		m_pPlayer->SetIsTransformed(true);
		m_pPlayer->GetStateMachine()->ChangeState(m_pPlayer->m_pPlayerState["TransformIdle"]);
		break;
	case SDLK_n: // return normal test
		m_pPlayer->SetIsTransformed(false);
		m_pPlayer->GetStateMachine()->ChangeState(m_pPlayer->m_pPlayerState["Idle"]);
		break;
	case  SDLK_KP_ENTER: // pause game
	case  SDLK_RETURN:
		
		if (m_currentGameState == GameState::playing || m_currentGameState == GameState::paused)
		{

			if (m_currentGameState == GameState::paused)
			{
				m_currentGameState = GameState::playing;
				m_pBackgroundMusic->Resume();
			}
			else
			{
				m_PauseSound->Play(0);
				m_currentGameState = GameState::paused;
				m_pBackgroundMusic->Pause();
			}

			m_pHUD->ResetPauseTimer();
		}
		
		break;

	}
}
void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	m_pInterfaceManager->HandleInputs(e);
}
void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
}
void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	
}
void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{

}

void Game::ShowGameInstructions()
{
	std::cout << " Game Instructions \n \n";
	std::cout << " Movement: \n";
	std::cout << "\t Left and Right arrows: move left and right \n";
	std::cout << " Actions: \n";
	std::cout << "\t Down arrow: crough \n";
	std::cout << "\t Up arrow: Climb platforms (while ledge grabbing) \n";
	std::cout << "\t Z / W: Jump, keep pressing for ledge grab / higher jump on trampolines \n";
	std::cout << "\t X: Attack \n";
	std::cout << "\t M: toggle music (on / off) \n";
}
void Game::CheckGameState()
{
	if (m_pPlayer->GetIsGameOver())
	{
		m_currentGameState = GameState::game_over;
	}
	else if (m_pInterfaceManager->GetIsGameStarted() && m_currentGameState != GameState::paused)
	{
		m_currentGameState = GameState::playing;
	}
	else if (m_pInterfaceManager->GetIsRestartActivated() && m_pPlayer->GetIsGameOver())
	{
		RestartGame();
	}


}
#pragma endregion
#pragma region CleanUp
void Game::Cleanup()
{
	delete m_pBackground;
	delete m_pLevel;
	delete m_pPlayer;
	delete m_pCamera;
	delete m_pObjectManager;
	delete m_pEnemyManager;
	delete m_pHUD;
	delete m_pInterfaceManager;
	delete m_pBackgroundMusic;
	delete m_pIntroMusic;
	delete m_pGameOverMusic;
	delete m_PauseSound;
}
void Game::RestartGame()
{
	Cleanup();
	Initialize();
	m_currentGameState = GameState::startscreen;
}
#pragma endregion
