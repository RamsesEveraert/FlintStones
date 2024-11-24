#pragma once
#include <vector>
#include "Camera.h"



class Texture;

class Background final
{
public:

	Background(const Rectf& cam, bool isTitleScreen);

	Background(const Background& other) = delete;
	Background& operator=(const Background& other) = delete;
	Background(Background&& other) = delete;
	Background& operator=(Background&& other) = delete;

	~Background();

	void Draw() const;
	void LoopBackground(float elapsedSec, bool isfacingLeft);
	void UpdateClouds(float elapsedSec);

	void SetBgPosition(float x, float y);
	void SetParallax(bool isActive);

private:

	void CreateBackground();
	void CreateClouds();
	void CreateSea();

	void InitBgPositions();
	void DeleteBackground();

	void DrawBackgrounds() const;
	void DrawClouds() const;
	void DrawSea() const;

	void DeleteClouds();
	void DeleteSea();

	bool m_IsTitleScreen;
	bool m_IsParallaxActive;

	Texture* m_pBlueBackground;

	std::vector<Texture*> m_pBackgroundElements;
	std::vector<Texture*> m_pClouds;
	std::vector<Texture*> m_pSea;


	std::vector<Rectf> m_DestRectBg;
	std::vector<Rectf> m_DestRectCloud;
	std::vector<Rectf> m_DestRectSea;
	std::vector<float> m_BgSpeed;
	const int m_AmountBackgrounds;

	Rectf m_Camera;
	const Point2f m_BgOffset;
	Rectf m_Background;




};
