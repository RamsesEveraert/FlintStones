#pragma once
#include "Shark.h"

class TransportShark final : public Shark
{

public:

	TransportShark(Level* level, const Rectf& shape, const Vector2f& speed, int fps);
	~TransportShark() = default;

	TransportShark(const TransportShark& other) = delete;
	TransportShark& operator=(const TransportShark& other) = delete;
	TransportShark(TransportShark&& other) = delete;
	TransportShark& operator=(TransportShark&& other) = delete;

	virtual void UpdatePosition(Entity& entity, float elapsedSec) override;
	virtual void Update(float elapsedSec) override;

	virtual void MoveShark(Entity& entity, float elapsedSec) override;
	

private:

	virtual void UpdateAnimations(float elapsedSec);

};

