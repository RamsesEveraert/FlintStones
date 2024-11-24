#include "pch.h"
#include "RotatingStars.h"
#include "AnimatedSprite.h"

RotatingStars::RotatingStars(const Point2f& centre, float spriteW, float spriteH, int nrFrames)
	: WorldObjects(centre, spriteW, spriteH, nrFrames)
{
	CreateObject("RotatingStar", 0.f, 9);
}


