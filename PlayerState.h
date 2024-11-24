#pragma once
#include <chrono>

class Player;
class PlayerStateMachine;
class PlayerData;

class PlayerState
{
public:
	PlayerState(Player* player,  PlayerStateMachine* stateMachine,  PlayerData* data, const std::string& animation);
	virtual ~PlayerState() = default;

	PlayerState(const PlayerState& other) = delete;
	PlayerState& operator=(const PlayerState& other) = delete;
	PlayerState(PlayerState&& other) = delete;
	PlayerState& operator=(PlayerState&& other) = delete;


	virtual void Enter();
	virtual void Exit();
	virtual void LogicUpdate(float elapsedSec);
	virtual void PhysicsUpdate(float elapsedSec);
	virtual void DoChecks();

protected:

	virtual void HandleInputs(float elapsedSec);

	Player* m_pPlayer;
	PlayerStateMachine* m_pStateMachine;
	PlayerData* m_pPlayerData;


	std::string m_AnimationName;

	bool m_IsAnimationFinished, m_IsInputLocked, m_CanMove, m_IsAttacking;
	bool m_CanAttack, m_IsJumpLocked;

	const Uint8* m_pStates;

	float m_StartTime; // begin of a state

private:

	
};

