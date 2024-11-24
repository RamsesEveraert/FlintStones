#pragma once
#include <vector>

class AnimatedSprite;
class Texture;
class Player;
class Background;

class InterfaceManager final
{
public:

	enum class GameScreenState
	{
		gameover,
		titlescreen_phase1,
		titlescreen_phase2,
		configuration,
		none
	};

	InterfaceManager(Player* player, float screenWidth, float screenHeight);

	InterfaceManager(const InterfaceManager& other) = delete;
	InterfaceManager& operator=(const InterfaceManager& other) = delete;
	InterfaceManager(InterfaceManager&& other) = delete;
	InterfaceManager& operator=(InterfaceManager&& other) = delete;

	~InterfaceManager();

	void DrawTitleScreen() const;
	void DrawStageEndScreen() const;
	void DrawGameOverScreen() const;

	void Update(float elapsedSec);

	bool GetIsRestartActivated() const;
	bool GetIsGameStarted() const;

	void SetGameScreenState(GameScreenState state);

	void HandleInputs(const SDL_KeyboardEvent& e);

private:

	enum class OptionButton
	{
		start, // kon continue niet gebruiken (reserved)
		options,
		exit,
		none
	};


	void UpdatePressToStart(float elapsedSec);
	void UpdateOptionButton(float elapsedSec);
	void UpdateTitleParallax(float elapsedSec);

	void SetupSprites();

	void DeleteSprites();

	bool m_IsRestartActivated;
	bool m_IsGameStarted;

	int m_FlashFrames;

	Player* m_pPlayer;
	Background* TitleScreenBg;

	OptionButton m_Option;
	GameScreenState m_CurrentScreenState;

	const float m_ScreenWidth, m_ScreenHeight, m_GameScale;
	Rectf m_Background;

	Texture* m_TitleScreenText;

	AnimatedSprite* m_pPressStart;
	Rectf m_PositionPressStat;

	AnimatedSprite* m_pGameOverAnimation;
	Rectf m_ShapeGameOverAnimation;

	Texture* m_pTextureGameOver;
	Rectf m_DstGameOverText;

	Texture* m_GameOverScreen;

	AnimatedSprite* m_SelectionButton1, *m_SelectionButton2;
	Rectf m_PosSelectionButton1, m_PosSelectionButton2;

	AnimatedSprite* m_StartButton, * m_OptionButton;
	Rectf m_posStartButton, m_posOptionButton;



};

