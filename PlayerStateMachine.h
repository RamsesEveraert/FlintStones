#pragma once
class PlayerState;

class PlayerStateMachine final
{
public:
	PlayerStateMachine();
	~PlayerStateMachine() = default;

	PlayerStateMachine(const PlayerStateMachine& other) = delete;
	PlayerStateMachine& operator=(const PlayerStateMachine& other) = delete;
	PlayerStateMachine(PlayerStateMachine&& other) = delete;
	PlayerStateMachine& operator=(PlayerStateMachine&& other) = delete;

	PlayerState* GetCurrentState();


	const PlayerState* GetPreviousState();
	void SetPreviousState(PlayerState* PreviousState);

	void Initialize(PlayerState* playerState);
	void ChangeState(PlayerState* newState);

private:
	PlayerState* m_pCurrentState;
	PlayerState* m_PreviousState;
};

