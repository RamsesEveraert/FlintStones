#pragma once
#include "PlayerTransformedState.h"

class PlayerTransformIdleState final : public PlayerTransformedState
{
public:

	PlayerTransformIdleState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerTransformIdleState() = default;

	PlayerTransformIdleState(const PlayerTransformIdleState& other) = delete;
	PlayerTransformIdleState& operator=(const PlayerTransformIdleState& other) = delete;
	PlayerTransformIdleState(PlayerTransformIdleState&& other) = delete;
	PlayerTransformIdleState& operator=(PlayerTransformIdleState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	void HandleInputs(float elapsedSec);
};

