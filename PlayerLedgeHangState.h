#pragma once
#include "PlayerState.h"

class PlayerLedgeHangState final : public PlayerState
{
public:

	PlayerLedgeHangState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerLedgeHangState() = default;

	PlayerLedgeHangState(const PlayerLedgeHangState& other) = delete;
	PlayerLedgeHangState& operator=(const PlayerLedgeHangState& other) = delete;
	PlayerLedgeHangState(PlayerLedgeHangState&& other) = delete;
	PlayerLedgeHangState& operator=(PlayerLedgeHangState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	void HandleInputs(float elapsedSec);
};

