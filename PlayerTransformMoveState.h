#pragma once
#include "PlayerTransformedState.h"

class PlayerTransformMoveState final : public PlayerTransformedState
{
public:

	PlayerTransformMoveState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerTransformMoveState() = default;

	PlayerTransformMoveState(const PlayerTransformMoveState& other) = delete;
	PlayerTransformMoveState& operator=(const PlayerTransformMoveState& other) = delete;
	PlayerTransformMoveState(PlayerTransformMoveState&& other) = delete;
	PlayerTransformMoveState& operator=(PlayerTransformMoveState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	void HandleInputs(float elapsedSec);
};

