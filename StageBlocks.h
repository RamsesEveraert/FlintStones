#pragma once

class AnimatedSprite;

class StageBlocks final
{
public:
	StageBlocks(const Rectf& shape);

	StageBlocks(const StageBlocks& other) = delete;
	StageBlocks& operator=(const StageBlocks& other) = delete;
	StageBlocks(StageBlocks&& other) = delete;
	StageBlocks& operator=(StageBlocks&& other) = delete;

	~StageBlocks();

	void Update(float elapsedSec);
	void Draw() const;

	const Rectf GetShape() const;
	
private:

	void SetupAnimations() const;

	AnimatedSprite* m_pFloorBlock;
	const Rectf m_Shape;

};