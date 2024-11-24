#pragma once
#include "WorldObjects.h"

class AnimatedSprite;

class Balloon final : public WorldObjects
{
public:

	Balloon(const Point2f& centre, float spriteW, float spriteH, int nrFrames);
	~Balloon() = default;

	Balloon(const Balloon& other) = delete;
	Balloon& operator=(const Balloon& other) = delete;
	Balloon(Balloon&& other) = delete;
	Balloon& operator=(Balloon&& other) = delete;

private:

};

