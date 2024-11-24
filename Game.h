#pragma once

class Background;
class Level;
class Player;
class Camera;
class ObjectManager;
class EnemyManager;
class HUD;
class InterfaceManager;
class SoundStream;
class SoundEffect;


class Game final
{
public:

	explicit Game(const Window& window);

	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game(Game&& other) = delete;
	Game& operator=(Game&& other) = delete;

	~Game();

	void Update(float elapsedSec);
	void Draw() const;


	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e);
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e);

private:


	enum class GameState
	{
		startscreen, playing, paused, game_over
	};

	//**********  FUNCTIONS  **********//

	void ClearBackground() const;

	void Initialize();
	
	void CreatePlayer();
	void InitializeMainSounds();

	void Cleanup();

	void CheckGameState();

	void RestartGame();

	void ShowGameInstructions();


	
	// temporary test

	void TestTextFileRead();


	//********* DATA MEMBERS  ***************//

	const Window m_Window;
	const float m_GameScale;
	bool m_IsIntroPlayed;
	bool m_IsBgMusicPlaying;
	bool m_IsGameOverMusicPlaying;
	bool m_IsMusicActivated;


	GameState m_currentGameState;

	Background* m_pBackground;
	Level* m_pLevel;
	Player* m_pPlayer;
	Camera* m_pCamera;
	ObjectManager* m_pObjectManager;
	EnemyManager* m_pEnemyManager;
	HUD* m_pHUD;
	InterfaceManager* m_pInterfaceManager;

	SoundStream* m_pBackgroundMusic;
	SoundStream* m_pIntroMusic;
	SoundStream* m_pGameOverMusic;

	SoundEffect* m_PauseSound;


};