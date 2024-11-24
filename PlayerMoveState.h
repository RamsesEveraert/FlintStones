#pragma once
#include "PlayerGroundedState.h"

class PlayerMoveState final : public PlayerGroundedState
{
public:
	PlayerMoveState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerMoveState() = default;

	PlayerMoveState(const PlayerMoveState& other) = delete;
	PlayerMoveState& operator=(const PlayerMoveState& other) = delete;
	PlayerMoveState(PlayerMoveState&& other) = delete;
	PlayerMoveState& operator=(PlayerMoveState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:
	virtual void HandleInputs(float elapsedSec) override;
};

