#pragma once
#include "PlayerState.h"

class PlayerLedgeClimbState final : public PlayerState
{
public:

	PlayerLedgeClimbState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerLedgeClimbState() = default;

	PlayerLedgeClimbState(const PlayerLedgeClimbState& other) = delete;
	PlayerLedgeClimbState& operator=(const PlayerLedgeClimbState& other) = delete;
	PlayerLedgeClimbState(PlayerLedgeClimbState&& other) = delete;
	PlayerLedgeClimbState& operator=(PlayerLedgeClimbState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	void HandleInputs(float elapsedSec);
	const float m_ClimbOffset;
};

