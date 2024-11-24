#pragma once
#include "utils.h"
#include <unordered_map>

class Texture;

class FontManager final // NOT USED YET
{
public:
	using FontMap = std::unordered_map<char, int>;

	FontManager(const std::string& fontPath, int charW, int charH, FontMap map);
	~FontManager();

	void DrawFont(const std::string& text, float scale = 1.f);

private:
	void DeleteFont();

	Texture* m_pFontTexture;
	std::vector<Rectf> m_charClipRects;
	FontMap m_Map;
};


/*

					CREDITS:

				- hulp Liam


*/