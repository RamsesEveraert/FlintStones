#pragma once
#include "PlayerGroundedState.h"

class PlayerCrouchState final: public PlayerGroundedState
{
public:
	PlayerCrouchState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerCrouchState() = default;

	PlayerCrouchState(const PlayerCrouchState& other) = delete;
	PlayerCrouchState& operator=(const PlayerCrouchState& other) = delete;
	PlayerCrouchState(PlayerCrouchState&& other) = delete;
	PlayerCrouchState& operator=(PlayerCrouchState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	bool m_IsNextIdle;

};

