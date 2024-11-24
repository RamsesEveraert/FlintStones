#pragma once
#include <vector>
#include <string>

class Camera;
class Player;
class AnimatedSprite;
class Texture;

class HUD final
{

public:

	HUD(const Camera* camera, const Player* player);
	~HUD();

	HUD(const HUD& other) = delete;
	HUD& operator=(const HUD& other) = delete;
	HUD(HUD&& other) = delete;
	HUD& operator=(HUD&& other) = delete;

	void Draw(bool isPaused) const;

	void Update(float elapsedSec);
	void UpdatePause(float elapsedSec);

	void ResetPauseTimer();

private:

	void SetupSprites();

	void DrawHearts() const;

	void UpdateHearts(float elapsedSec);
	void UpdateScore(float elapsedSec);
	void UpdateCoins(float elapsedSec);
	void UpdateLives(float elapsedSec);
	
	
	void SetupCountTexture(const int maxElements, std::vector<AnimatedSprite*>& spriteVector);
	void DrawCounter(const AnimatedSprite* symbol, const std::vector<AnimatedSprite*>& counterSprite, const std::string& score) const;

	void DeleteSprites();

	bool m_IsPaused;
	int m_PauseTimer;

	const Player* m_pPlayer;

	const Camera* m_Camera;
	const float m_CameraScale;

	const int m_MaxHearts, m_MinHearts, m_MaxNumbers, m_MaxCoinSprites;
	const float m_Offset, m_Gap;

	std::vector< Rectf> m_PositionHearts;

	
	AnimatedSprite* m_pLivesSymbol, *m_pScoreSymbol, *m_pCoinSymbol, *m_pPause;
	std::vector <AnimatedSprite*> m_pHearts, m_pLivesCountSprite, m_pScoreCountSprite, m_pCoinCountSprite;
	std::string m_LivesCount, m_ScoreCount, m_CoinCount;

	Rectf m_LiveSymbolShape, m_ScoreSymbolShape, m_CoinSymbolShape;
	Rectf m_PosLives, m_PosCoinPoints, m_PosPause;

};


