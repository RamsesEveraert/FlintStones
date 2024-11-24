#include "pch.h"
#include "Balloon.h"
#include "AnimatedSprite.h"

Balloon::Balloon(const Point2f& centre, float spriteW, float spriteH, int nrFrames)
	: WorldObjects(centre, spriteW, spriteH, nrFrames)
{
	CreateObject("WigglingBalloon", 27.f, 6);
}



