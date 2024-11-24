#pragma once
#include "PlayerState.h"

class PlayerTransformedState : public PlayerState
{
public:
	PlayerTransformedState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	virtual ~PlayerTransformedState() = default;

	PlayerTransformedState(const PlayerTransformedState& other) = delete;
	PlayerTransformedState& operator=(const PlayerTransformedState& other) = delete;
	PlayerTransformedState(PlayerTransformedState&& other) = delete;
	PlayerTransformedState& operator=(PlayerTransformedState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

protected:

	virtual void HandleInputs(float elapsedSec);

private:

	bool m_HasShoot;
};

