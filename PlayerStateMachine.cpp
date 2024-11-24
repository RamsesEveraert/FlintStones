#include "pch.h"
#include "PlayerStateMachine.h"
#include "PlayerMoveState.h"

PlayerStateMachine::PlayerStateMachine()
	: m_pCurrentState {}
	, m_PreviousState{}
{
}

 PlayerState* PlayerStateMachine::GetCurrentState()
{
	return m_pCurrentState;
}

const PlayerState* PlayerStateMachine::GetPreviousState()
{
	return m_PreviousState;
}

void PlayerStateMachine::SetPreviousState(PlayerState* PreviousState)
{
	m_PreviousState = PreviousState;
}

void PlayerStateMachine::Initialize(PlayerState* startingState) 
{
	m_pCurrentState = startingState;
	m_pCurrentState->Enter();
}

void PlayerStateMachine::ChangeState(PlayerState* newState)
{
	m_pCurrentState->Exit();
	m_pCurrentState = newState;
	m_pCurrentState->Enter();
}



/*

				Source: https://gameprogrammingpatterns.com/state.html

*/