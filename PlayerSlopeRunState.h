#pragma once
#include "PlayerGroundedState.h"

class PlayerSlopeRunState final : public PlayerGroundedState
{
public:

	PlayerSlopeRunState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerSlopeRunState() = default;

	PlayerSlopeRunState(const PlayerSlopeRunState& other) = delete;
	PlayerSlopeRunState& operator=(const PlayerSlopeRunState& other) = delete;
	PlayerSlopeRunState(PlayerSlopeRunState&& other) = delete;
	PlayerSlopeRunState& operator=(PlayerSlopeRunState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	void HandleInputs(float elapsedSec);
};

