#pragma once
#include "PlayerState.h"
class PlayerGroundedState : public PlayerState
{
public:

	PlayerGroundedState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	virtual ~PlayerGroundedState() = default;

	PlayerGroundedState(const PlayerGroundedState& other) = delete;
	PlayerGroundedState& operator=(const PlayerGroundedState& other) = delete;
	PlayerGroundedState(PlayerGroundedState&& other) = delete;
	PlayerGroundedState& operator=(PlayerGroundedState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

protected:

	virtual void HandleInputs(float elapsedSec);

private:
	bool m_IsGrounded;
};

