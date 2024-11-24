#pragma once
#include "PlayerTransformedState.h"

class PlayerTransformAttackState final : public PlayerTransformedState
{
public:

	PlayerTransformAttackState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerTransformAttackState() = default;

	PlayerTransformAttackState(const PlayerTransformAttackState& other) = delete;
	PlayerTransformAttackState& operator=(const PlayerTransformAttackState& other) = delete;
	PlayerTransformAttackState(PlayerTransformAttackState&& other) = delete;
	PlayerTransformAttackState& operator=(PlayerTransformAttackState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	void HandleInputs(float elapsedSec);

};

