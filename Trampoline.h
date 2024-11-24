#include "WorldObjects.h"

class Entity;

class Trampoline final : public WorldObjects
{
public:

	Trampoline(const Point2f& centre, float spriteW, float spriteH, int nrFrames);
	~Trampoline() = default;

	Trampoline(const Trampoline& other) = delete;
	Trampoline& operator=(const Trampoline& other) = delete;
	Trampoline(Trampoline&& other) = delete;
	Trampoline& operator=(Trampoline&& other) = delete;

	virtual void Update(float elapsedSec);

	void ActivateTrampoline(Entity& entity);

private:

	const float m_JumpHeight, m_ExtraJumpHeight;
	bool m_IsTrampolineActivate;


};

