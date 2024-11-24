#pragma once
#include "WorldObjects.h"

class RotatingStars final : public WorldObjects
{
public:

	RotatingStars(const Point2f& centre, float spriteW, float spriteH, int nrFrames);
	~RotatingStars() = default;

	RotatingStars(const RotatingStars& other) = delete;
	RotatingStars& operator=(const RotatingStars& other) = delete;
	RotatingStars(RotatingStars&& other) = delete;
	RotatingStars& operator=(RotatingStars&& other) = delete;

private:

};

