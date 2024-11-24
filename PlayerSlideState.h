#pragma once
#include "PlayerGroundedState.h"


class PlayerSlideState final : public PlayerGroundedState
{
public:
	PlayerSlideState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
	~PlayerSlideState() = default;

	PlayerSlideState(const PlayerSlideState& other) = delete;
	PlayerSlideState& operator=(const PlayerSlideState& other) = delete;
	PlayerSlideState(PlayerSlideState&& other) = delete;
	PlayerSlideState& operator=(PlayerSlideState&& other) = delete;

	virtual void Enter() override;
	virtual void Exit() override;
	virtual void LogicUpdate(float elapsedSec) override;
	virtual void PhysicsUpdate(float elapsedSec) override;
	virtual void DoChecks() override;

private:

	void StartSlideTimer(float elapsedSec);
};

