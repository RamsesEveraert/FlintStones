#pragma once
#include "PlayerGroundedState.h"
#include "PlayerStateMachine.h"
#include "Player.h"

class PlayerLandState final : public PlayerGroundedState
{
public:
	PlayerLandState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerLandState() = default;

	PlayerLandState(const PlayerLandState& other) = delete;
	PlayerLandState& operator=(const PlayerLandState& other) = delete;
	PlayerLandState(PlayerLandState&& other) = delete;
	PlayerLandState& operator=(PlayerLandState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	void HandleInputs(float elapsedSec);

};