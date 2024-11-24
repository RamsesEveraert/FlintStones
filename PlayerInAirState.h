#pragma once
#include "PlayerAbilityState.h"
class PlayerInAirState final : public PlayerAbilityState
{
public:
	PlayerInAirState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerInAirState() = default;

	PlayerInAirState(const PlayerInAirState& other) = delete;
	PlayerInAirState& operator=(const PlayerInAirState& other) = delete;
	PlayerInAirState(PlayerInAirState&& other) = delete;
	PlayerInAirState& operator=(PlayerInAirState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:
	void HandleInputs(float elapsedSec);
};

