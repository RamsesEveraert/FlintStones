#pragma once
#include "PlayerState.h"

class PlayerChargingState final : public PlayerState
{
public:

	PlayerChargingState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerChargingState() = default;

	PlayerChargingState(const PlayerChargingState& other) = delete;
	PlayerChargingState& operator=(const PlayerChargingState& other) = delete;
	PlayerChargingState(PlayerChargingState&& other) = delete;
	PlayerChargingState& operator=(PlayerChargingState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	void HandleInputs(float elapsedSec);
};

