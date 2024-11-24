#pragma once
#include "PlayerState.h"

class PlayerChargedMoveState final : public PlayerState
{
	public:

		PlayerChargedMoveState(Player* player, PlayerStateMachine* stateMachine, PlayerData* playerData, const std::string& animation);
		~PlayerChargedMoveState() = default;

		PlayerChargedMoveState(const PlayerChargedMoveState& other) = delete;
		PlayerChargedMoveState& operator=(const PlayerChargedMoveState& other) = delete;
		PlayerChargedMoveState(PlayerChargedMoveState&& other) = delete;
		PlayerChargedMoveState& operator=(PlayerChargedMoveState&& other) = delete;

		virtual void Enter() override;
		virtual void Exit() override;
		virtual void LogicUpdate(float elapsedSec) override;
		virtual void PhysicsUpdate(float elapsedSec) override;
		virtual void DoChecks() override;

	private:

		void HandleInputs(float elapsedSec);


};

