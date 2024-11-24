#include "pch.h"
#include "FontManager.h"
#include "Texture.h"

FontManager::FontManager(const std::string& fontPath, int charW, int charH, FontMap map)
	: m_pFontTexture{ new Texture(fontPath) }
	, m_charClipRects{}
	, m_Map{ map }
{
	for (size_t idx{}; idx < map.size(); ++idx)
	{
		Rectf clipRect{};
		clipRect.width = float(charW);
		clipRect.bottom = clipRect.height = float(charH);
		clipRect.left = float(charW * idx);

		m_charClipRects.push_back(clipRect);
	}
}

FontManager::~FontManager()
{
	DeleteFont();
}

void FontManager::DrawFont(const std::string& text, float scale)
{
	for (size_t idx{}; idx < text.length(); ++idx)
	{
		int charPos{ m_Map[text[idx]] };
		const Rectf& clipRect{ m_charClipRects[charPos] };

		glPushMatrix();

		Point2f bottomLeft{ clipRect.width * idx, 0 };
		glTranslatef(bottomLeft.x, bottomLeft.y, 0.0f);

		m_pFontTexture->Draw(Point2f{}, clipRect);

		glPopMatrix();
	}
}

void FontManager::DeleteFont()
{
	m_charClipRects.clear();

	delete m_pFontTexture;
	m_pFontTexture = nullptr;
}
