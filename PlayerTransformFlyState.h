#pragma once
#include "PlayerTransformedState.h"

class SoundEffect;

class PlayerTransformFlyState final : public PlayerTransformedState
{
public:

	PlayerTransformFlyState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerTransformFlyState();

	PlayerTransformFlyState(const PlayerTransformFlyState& other) = delete;
	PlayerTransformFlyState& operator=(const PlayerTransformFlyState& other) = delete;
	PlayerTransformFlyState(PlayerTransformFlyState&& other) = delete;
	PlayerTransformFlyState& operator=(PlayerTransformFlyState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	void HandleInputs(float elapsedSec);

	SoundEffect* m_pJumpSound;
};

