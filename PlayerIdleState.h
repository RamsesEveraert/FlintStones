#pragma once
#include "PlayerGroundedState.h"

class PlayerIdleState final : public PlayerGroundedState
{
public:
	PlayerIdleState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerIdleState() = default;

	PlayerIdleState(const PlayerIdleState& other) = delete;
	PlayerIdleState& operator=(const PlayerIdleState& other) = delete;
	PlayerIdleState(PlayerIdleState&& other) = delete;
	PlayerIdleState& operator=(PlayerIdleState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:
	virtual void HandleInputs(float elapsedSec);
	void StartDance(float elapsedSec);
};

