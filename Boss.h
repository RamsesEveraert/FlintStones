#pragma once
#include "Entity.h"

class Boss final : public Entity
{
public:
	Boss(Level* level, const Rectf& shape, float horSpeed, float jumpSpeed, int fps, float slideDistance);
	~Boss() override;

	Boss(const Boss& other) = delete;
	Boss& operator=(const Boss& other) = delete;
	Boss(Boss&& other) = delete;
	Boss& operator=(Boss&& other) = delete;

	virtual void Update(float elapsedSec) override;
	void UpdatePosition(float elapsedSec, Entity& player);


private:

		enum class BossState
		{
			attack,
			hit,
			surrender
		};

		void Initialize();
		void SetupAnimations();
		void HandleWallCollision(float elapsedSec);

		void HandleStates();

		void AttackPlayer(float elapsedSec, const Entity& player);


		BossState m_CurrentState;

		std::string m_CurrentAnimation;

		int m_Fps;
		int m_WallCount;
		const float m_SlideDistance;
		float m_Timer;


};

