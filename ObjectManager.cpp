#include "pch.h"
#include "ObjectManager.h"
#include "Player.h"
#include "Entity.h"
#include "RotatingStars.h"
#include "Balloon.h"
#include "Trampoline.h"
#include "Egg.h"
#include "Wall.h"
#include "SoundEffect.h"


ObjectManager::ObjectManager()

	: m_BalloonPopSound { new SoundEffect("Resources/Audio/Balloon_Hit.wav")}
	, m_PowerUpSound { new SoundEffect("Resources/Audio/Flintstones_PowerUp.wav") }
	, m_TrampolineJumpSound{ new SoundEffect("Resources/Audio/Trampoline.wav") }

{
	m_PowerUpSound->SetVolume(35);
	InitializeObjects();
}

ObjectManager::~ObjectManager()
{
	delete m_BalloonPopSound;
	delete m_PowerUpSound;
	delete m_TrampolineJumpSound;

	DeleteObject();
}


const size_t ObjectManager::GetSizeObjects() const
{
	return m_pObject.size();
}
const std::vector<WorldObjects*> ObjectManager::GetObjects() const
{
	return m_pObject;
}
bool ObjectManager::HitItem(Entity& entity)
{

	for (size_t index{}; index < m_pObject.size(); ++index)
	{

		Player* pPlayer = dynamic_cast<Player*>(&entity);
		Balloon* pBallon = dynamic_cast<Balloon*>(m_pObject[index]);
		Egg* pEgg = dynamic_cast<Egg*>(m_pObject[index]);
		Trampoline* pTrampoline = dynamic_cast<Trampoline*>(m_pObject[index]);
		RotatingStars* pRotatingStars = dynamic_cast<RotatingStars*>(m_pObject[index]);

		

		if (pRotatingStars && m_pObject[index]->IsOverlapping(entity.GetHitbox()))
		{
			int scorePoints{ 50 };

			m_PowerUpSound->Play(0);

			pPlayer->AddCoins();
			pPlayer->AddScore(scorePoints);
			RemoveObject(index);
			return true;
		}

		else if (pEgg)
		{
			switch (pEgg->GetState())
			{
			case Egg::States::initial:
				
				if(m_pObject[index]->IsOverlapping(entity.GetHitbox()))
					pEgg->SetState(Egg::States::activated);

				break;
			case Egg::States::activated:

				if (entity.GetIsAttacking() && m_pObject[index]->IsOverlapping(entity.GetHitbox()))
					pEgg->SetState(Egg::States::hatched);

				utils::IsOverlapping(entity.GetShape(), pEgg->GetShape())
					? pEgg->SetParent(nullptr)
					: pEgg->SetParent(&entity);	

				break;
			case Egg::States::hatched:
				if (!pPlayer->GetCanTransform() && m_pObject[index]->IsOverlapping(entity.GetHitbox()))
				{
					ObjectManager::RemoveObject(index);
					pPlayer->SetCanTransform(true);
				}
				break;
			}

		}

		if (pBallon && entity.GetIsAttacking() && m_pObject[index]->IsOverlapping(entity.GetHitbox()))
		{
			int scorePoints{ 75 };

			m_BalloonPopSound->Play(0);

			pPlayer->AddScore(scorePoints);
			ObjectManager::PopBalloon(m_pObject, index, entity.IsFacingLeft());
			return true;
		}
		

		if (pTrampoline && entity.GetVelocity().y <= 0 && m_pObject[index]->IsOverlapping(entity.GetHitbox()))
		{
			m_TrampolineJumpSound->Play(0);
			pTrampoline->ActivateTrampoline(entity);
			return true;
		}
		
	}

	return false;
}


// behouden!! later  


#pragma region GeneralFunctions
void ObjectManager::Draw() const
{
	for (WorldObjects* pObject : m_pObject)
	{
		if (pObject) pObject->Draw();
	}
}

void ObjectManager::Update(float elapsedSec)
{
	for (WorldObjects* pObject : m_pObject)
	{
		if(pObject) pObject->Update(elapsedSec);
	}
}

WorldObjects* ObjectManager::CreateRotatingStar(const Point2f& centre, float spriteW, float spriteH, int nrFrames)
{
	m_pObject.push_back(new RotatingStars(centre, spriteW, spriteH, nrFrames));
	return m_pObject.back();
}
WorldObjects* ObjectManager::CreateBalloons(const Point2f& centre, float spriteW, float spriteH, int nrFrames)
{
	m_pObject.push_back(new Balloon(centre, spriteW, spriteH, nrFrames));
	return m_pObject.back();
}
WorldObjects* ObjectManager::CreateTrampolines(const Point2f& centre, float spriteW, float spriteH, int nrFrames)
{
	m_pObject.push_back(new Trampoline(centre, spriteW, spriteH, nrFrames));
	return m_pObject.back();
}
WorldObjects* ObjectManager::CreateEgg(const Point2f& centre, float spriteW, float spriteH, int nrFrames)
{
	m_pObject.push_back(new Egg(centre, spriteW, spriteH, nrFrames));
	return m_pObject.back();
}

void ObjectManager::RemoveObject(size_t index)
{
	delete m_pObject[index];
	m_pObject[index] = m_pObject.back();
	m_pObject.pop_back();
}
void ObjectManager::PopBalloon(std::vector<WorldObjects*> object, size_t index, bool isFacingLeft)
{
	Balloon* pBallon = dynamic_cast<Balloon*>(m_pObject[index]);

	if (pBallon)
	{
		int nrFrames{ 3 };
		float direction{ isFacingLeft ? -1.f : +1.f };
		float distance{ 30.f };
		Point2f pos{ pBallon->GetShape().left + direction * distance , pBallon->GetShape().bottom };

		ObjectManager::CreateRotatingStar(pos, pBallon->GetShape().width, pBallon->GetShape().height, nrFrames);
		RemoveObject(index);
	}
	
}
#pragma endregion 
#pragma region CleanUp
void ObjectManager::InitializeObjects()
{
	CreateRotatingStar(Point2f{ 405.f,165.f }, 27.f, 27.f, 3);
	CreateRotatingStar(Point2f{ 489.f,165.f }, 27.f, 27.f, 3);
	CreateRotatingStar(Point2f{ 1281.f,90.f }, 27.f, 27.f, 3);
	CreateRotatingStar(Point2f{ 1976.f,90.f }, 27.f, 27.f, 3);

	CreateBalloons(Point2f{ 601.f,154.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 1018.f,316.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 4929.f,155.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 5007.f,155.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 5220.f,155.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 5380.f,155.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 5414.f,155.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 5526.f,155.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 5693.f,155.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 5898.f,521.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 5930.f,521.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 5963.f,521.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 6736.f,153.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 6762.f,153.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 6803.f,153.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 6842.f,153.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 7009.f,153.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 7834.f,510.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 7860.f,430.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 7976.f,510.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 11167.f,350.f }, 27.f, 27.f, 3);
	CreateBalloons(Point2f{ 11257.f,350.f }, 27.f, 27.f, 3);

	CreateTrampolines(Point2f{ 1283.f,40.f }, 57.f, 25.f, 1);
	CreateTrampolines(Point2f{ 1977.f,40.f }, 57.f, 25.f, 1);

	CreateEgg(Point2f{ 6400.f, 154.f }, 27.f, 27.f, 1);
	CreateEgg(Point2f{ 10944.f, 347.f }, 27.f, 27.f, 1);
}
void ObjectManager::DeleteObject()
{
	for (size_t idx{}; idx < m_pObject.size(); ++idx)
	{
		if (m_pObject[idx])
		{
			delete m_pObject[idx];
			m_pObject[idx] = nullptr;
		}
	}
	m_pObject.clear();
}
#pragma endregion 



