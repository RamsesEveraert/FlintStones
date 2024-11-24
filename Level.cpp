#include "pch.h"
#include "Level.h"
#include "SVGParser.h"
#include "Texture.h"
#include "AnimatedSprite.h"
#include "Entity.h"
#include "PlayerStateMachine.h"
#include "PlatformManager.h"
#include "Wall.h"

Level::Level()
	: m_VerticesSurface{ }
	, m_pStage{ new Texture("Resources/Stage/Stage.png") }
	, m_pForeGround { new Texture("Resources/Stage/StageForeGround.png") }
	, m_pPlatforms { new PlatformManager() }
	, m_Boundaries{ 0, 0,m_pStage->GetWidth(), m_pStage->GetHeight() }
	, m_CheckPointWalls{}
	, m_NeededSprites {14}
	, m_BlWaterfall{ 6179.f, 122.f }
	, m_WallCount{ 2 }
	, m_AreWallsGone {false}
	
{
	Level::CreateFoam();
	Level::CreateWaterfall();
	Level::CreateMovingWater();
	Level::CreateStageVertices();
	Level::CreateCheckpointWalls();
	Level::CreateStartSign();
	Level::CreateSpawnPoints();
	Level::CreateWalls();
}

Level::~Level()
{
	Level::CleanUp();
}

#pragma region Initialization
void Level::CreateStartSign()
{
	m_pStartSign = new Texture("Resources/Objects/Objects.png");

	m_DstStartSign = Rectf{ 48.f, 61.f, 56.f,56.f };
	m_SrcStartSign = Rectf{ 0, 226.f, 56.f, 56.f };
}
void Level::CreateSpawnPoints()
{
	m_pSpawnPoints = new Texture("Resources/Objects/Objects.png");

	// spawn point 2

	m_DstSpawns.push_back(Rectf{ 2855.f,538.f,27.f,27.f });
	m_SrcSpawns.push_back(Rectf{ 0.f,81.f,27.f,27.f });

	// spawn point 3

	m_DstSpawns.push_back(Rectf{ 6850.f,474.f,27.f,27.f });
	m_SrcSpawns.push_back(Rectf{ 27.f,81.f,27.f,27.f });

	// spawn point 4

	m_DstSpawns.push_back(Rectf{ 9211.f,303.f,27.f,27.f });
	m_SrcSpawns.push_back(Rectf{ 54.f,81.f,27.f,27.f });


}
void Level::CreateMovingWater()
{
	for (size_t index{}; index <= m_NeededSprites; ++index)
	{
		m_pMovingWaterTop.push_back(new AnimatedSprite("Resources/Stage/MovingWater.png",318.f,24.f,1.f,3));
		m_pMovingWaterTop[index]->AddAnimation("MovingWater", 0.f, 0.f, 318.f, 13.f, 3);
		m_pMovingWaterTop[index]->SetFramesPerSec(7);
		m_pMovingWaterTop[index]->PlayAnimation("MovingWater");
	}
	for (size_t index{}; index <= m_NeededSprites; ++index)
	{
		m_pMovingWaterBottom.push_back(new AnimatedSprite("Resources/Stage/MovingWater.png", 318.f, 24.f, 1.f, 3));
		m_pMovingWaterBottom[index]->AddAnimation("MovingWater", 0.f, 24.f, 318.f, 13.f, 3);
		m_pMovingWaterBottom[index]->SetFramesPerSec(7);
		m_pMovingWaterBottom[index]->PlayAnimation("MovingWater");
	}
}
void Level::CreateWaterfall()
{
	m_pWaterfall = new Texture("Resources/Stage/Waterfall.png");
	m_DstWaterfall.push_back(Rectf{ m_BlWaterfall.x, m_BlWaterfall.y, m_pWaterfall->GetWidth(), m_pWaterfall->GetHeight() });
}
void Level::CreateFoam()
{
	m_pBottomFoam = new AnimatedSprite("Resources/Stage/BottomFoam.png", 239.f, 22.f,1.1f);
	m_pBottomFoam->AddAnimation("BottomFoam", 0.f, 0.f, 239.f, 22.f,2);
	m_pBottomFoam->SetFramesPerSec(6);
	m_pBottomFoam->PlayAnimation("BottomFoam");

	m_pTopFoam = new AnimatedSprite("Resources/Stage/TopFoam.png", 272.f, 7.f, 1.f);
	m_pTopFoam->AddAnimation("TopFoam", 0.f, 0.f, 272.f, 7.f, 2);
	m_pTopFoam->SetFramesPerSec(6);
	m_pTopFoam->PlayAnimation("TopFoam");

}
void Level::CreateWalls()
{
	m_pWalls.push_back(new Wall(Rectf{ 9095.f,304.f,32.f,81.f }));
	m_pWalls.push_back(new Wall(Rectf{ 9127.f,304.f,32.f,81.f }));
}
void Level::CreateStageVertices()
{
	std::string stageFile{ "Resources/Stage/Stage1.svg" };
	SVGParser::GetVerticesFromSvgFile(stageFile, m_VerticesSurface);
}
void Level::CreateCheckpointWalls()
{
	std::string stageFile{ "Resources/Stage/CheckpointWalls.svg" };
	SVGParser::GetVerticesFromSvgFile(stageFile, m_CheckPointWalls);
}
#pragma endregion
#pragma region DrawFunctions
void Level::Draw() const
{
	Level::DrawWaterfall();
	m_pPlatforms->DrawLogs();
	Level::DrawFoam();
	m_pStage->Draw();
	m_pPlatforms->DrawFloorBlocks();
	m_pStartSign->Draw(m_DstStartSign, m_SrcStartSign);
	Level::DrawSpawnPoints();
	Level::DrawMovingWater();
	Level::DrawWalls();


}
void Level::DrawForeGround() const
{
	m_pForeGround->Draw();
}
void Level::DrawSpawnPoints() const
{
	for (size_t index{}; index < m_DstSpawns.size(); ++index)
	{
		m_pSpawnPoints->Draw(m_DstSpawns[index], m_SrcSpawns[index]);
	}
}
void Level::DrawMovingWater() const
{
	for (size_t index{}; index <= m_NeededSprites; ++index)
	{
		m_pMovingWaterTop[index]->Draw();
		m_pMovingWaterBottom[index]->Draw();
	}
	
}
void Level::DrawFoam() const
{
	m_pBottomFoam->Draw();
	m_pTopFoam->Draw();
}
void Level::DrawWaterfall() const
{
	for (Rectf waterfall : m_DstWaterfall)
	{
		m_pWaterfall->Draw(waterfall);
	}
}

void Level::DrawWalls() const
{
	for (Wall* pWall : m_pWalls)
	{
		if(pWall) pWall->Draw();
	}
}

void Level::DrawRaycast(const Rectf& entityShape) const
{
	// Vertical collision up

	Point2f startVRayUp{ entityShape.left + 0.5f * entityShape.width, entityShape.bottom + 0.5f * entityShape.height};
	Point2f endVRayUp{ entityShape.left + 0.5f * entityShape.width,  entityShape.bottom + 0.75f * entityShape.height  + 1 };

	utils::SetColor(Color4f{ 0.f,1.f,0.f,1.f });
	utils::DrawLine(startVRayUp, endVRayUp, 3);

	// Horizontal Collision right

	Point2f startHRayRight{ entityShape.left + 0.5f * entityShape.width , entityShape.bottom + 0.5f * entityShape.height };
	Point2f endHRayRight{ entityShape.left + 0.75f * entityShape.width + 1, entityShape.bottom + 0.5f * entityShape.height };

	utils::SetColor(Color4f{ 1.f,1.f,1.f,1.f });
	utils::DrawLine(startHRayRight, endHRayRight, 3);

	// Horizontal Collision left 

	Point2f startHRayLeft{ entityShape.left + 0.5f * entityShape.width  , entityShape.bottom + 0.5f * entityShape.height};
	Point2f endHRayLeft{ entityShape.left - 1 , entityShape.bottom + 0.5f * entityShape.height };

	utils::SetColor(Color4f{ 0.f,0.f,1.f,1.f });
	utils::DrawLine(startHRayLeft, endHRayLeft, 3);
}

void Level::Update(float elapsedSec)
{
	Level::UpdateMovingWater(elapsedSec);
	Level::UpdateFoam(elapsedSec);
	Level::UpdatePlatforms(elapsedSec);
	Level::UpdateWall(elapsedSec);
}

void Level::UpdateMovingWater(float elapsedSec)
{
	for (size_t index{}; index <= m_NeededSprites; ++index)
	{
		Rectf MovingWaterTop{ 3415.f,86.f,318.f,13.f };
		Rectf MovingWaterBottom{ 3415.f,67.f,318.f,13.f };

		MovingWaterBottom.left = MovingWaterTop.left += index * MovingWaterTop.width;
		
		m_pMovingWaterTop[index]->Update(elapsedSec, MovingWaterTop);
		m_pMovingWaterBottom[index]->Update(elapsedSec, MovingWaterBottom);
	}
}
void Level::UpdateWaterfall(float elapsedSec)
{
	// todo: texture repeater??
}
void Level::UpdatePlatforms(float elapsedSec)
{
	m_pPlatforms->Update(elapsedSec);
}
void Level::UpdateFoam(float elapsedSec)
{
	Rectf dstBottomFoam{ 6181.f, 102.f, 239.f, 22.f };
	m_pBottomFoam->Update(elapsedSec, dstBottomFoam);

	Rectf dstTopFoam{ 6181.f, 488.f, 272.f, 7.f };
	m_pTopFoam->Update(elapsedSec, dstTopFoam);
}
void Level::UpdateWall(float elapsedSec)
{
	for (Wall* pWall : m_pWalls)
	{
		if (pWall)
		{
			pWall->Update(elapsedSec);
		}
	}
}
#pragma endregion
#pragma region Checks

void Level::HandleCollision(Entity& entity) const
{
	if (!entity.IsJumping() && entity.GetVelocity().y < 0)
	{
		Level::CheckIsOnGround(entity);
	}
	if (entity.GetVelocity().y > 0)
	{
		Level::CheckHitCeiling(entity);
	}
	if (entity.GetVelocity().y >= 0 || entity.GetVelocity().y <= 0)
	{
		Level::CheckWallHit(entity);
	}
}

bool Level::CheckIsOnGround(Entity& entity) const
{
	Rectf entityShape{ entity.GetShape() };

	Point2f startRay{ entityShape.left + 0.5f * entityShape.width, entityShape.bottom + 0.5f * entityShape.height};
	Point2f endRay{ entityShape.left + 0.5f * entityShape.width, entityShape.bottom - 1.f };

	utils::HitInfo hitInfo;
	
	for (const std::vector<Point2f>& surface : m_VerticesSurface)
	{
		if (entity.GetVelocity().y <= 0 && utils::Raycast(surface, startRay, endRay, hitInfo))
		{
			Rectf newShape{ entity.GetShape() };
			Vector2f newVelocity{ entity.GetVelocity() };

			newVelocity.y = 0;
			newShape.bottom = hitInfo.intersectPoint.y;

			entity.SetShape(newShape);
			entity.SetVelocity(newVelocity);
			return true;
		}

	}
	
		return (m_pPlatforms->IsOnGround(entity)) ? true : false;
}

bool Level::CheckHitCeiling(Entity& entity) const
{
	Rectf entityShape{ entity.GetShape() };

	Point2f startRay{ entityShape.left + 0.5f * entityShape.width,  entityShape.bottom + 0.5f * entityShape.height};
	Point2f endRay{ entityShape.left + 0.5f * entityShape.width,   entityShape.bottom + 1.1f * entityShape.height};

	utils::HitInfo hitInfo;

	for (const std::vector<Point2f>& surface : m_VerticesSurface)
	{
		if (utils::Raycast(surface, startRay, endRay, hitInfo))
		{
			Vector2f newVelocity{ entity.GetVelocity() };
			newVelocity.y = 0;
			entity.SetVelocity(newVelocity);
			return true;
		}

	}

	return false;
}
bool Level::CheckWallHit(Entity& entity) const
{
	Rectf entityShape(entity.GetShape());
	float rayLength{ entity.IsFacingLeft() ? -1.f : entityShape.width + 1 };

	if (entity.IsPlayer())
	{
		(entity.IsFacingLeft())
			? rayLength = 0.2f * entityShape.width 
			: rayLength = 0.75f * entityShape.width;
	}

	Point2f startRay{ entityShape.left + 0.5f * entityShape.width, entityShape.bottom + 0.5f * entityShape.height };
	Point2f endRay{ entityShape.left + rayLength, entityShape.bottom + 0.5f * entityShape.height };

	utils::HitInfo hitInfo;

	Rectf newShape{ entityShape };
	Vector2f newVelocity{ entity.GetVelocity() };

	for (const std::vector<Point2f>& surface : m_VerticesSurface)
	{
		if (utils::Raycast(surface, startRay, endRay, hitInfo))
		{
			(entity.IsPlayer())
				? newShape.left = hitInfo.intersectPoint.x - rayLength
				: newShape.left = hitInfo.intersectPoint.x - rayLength +1 ;
	
			(entity.IsPlayer())
				? newVelocity.x = 0
				: newVelocity.x *= -1;

			entity.SetShape(newShape);
			entity.SetVelocity(newVelocity);

			return true;
		}

	}

	for (Wall* wall : m_pWalls)
	{
		if (wall)
		{
			Point2f leftBottom{ wall->GetShape().left, wall->GetShape().bottom };
			Point2f LeftTop{ wall->GetShape().left, wall->GetShape().bottom + wall->GetShape().height };

			std::vector surfaceWall{ leftBottom, LeftTop };


			if (utils::Raycast(surfaceWall, startRay, endRay, hitInfo))
			{
				(entity.IsFacingLeft())
					? newShape.left = hitInfo.intersectPoint.x - rayLength
					: newShape.left = hitInfo.intersectPoint.x - rayLength;

				if (entity.IsPlayer())
				{
					newVelocity.x = 0;

					entity.SetShape(newShape);
					entity.SetVelocity(newVelocity);
					return true;
				}
				

				
			}
		}
		
	}

	



	//			OPTIONEEL LATER		- ALS CAMERA CLIP WERKT	//

	/*Point2f startLeftRay{ entity.GetShape().left + (entity.GetShape().width / 2) , entity.GetShape().bottom + (entity.GetShape().height / 2) };
	Point2f endLeftRay{ entity.GetShape().left + (entity.GetShape().width / 5) , entity.GetShape().bottom + (entity.GetShape().height / 2) };

	for (const std::vector<Point2f>& checkWall : m_CheckPointWalls)
	{
		if (utils::Raycast(checkWall, startRay, endRay, hitInfo))
		{
			if(entity.IsFacingLeft())
				newShape.left = hitInfo.intersectPoint.x - (entity.GetShape().width / 5);
			newVelocity.x = 0;

			entity.SetShape(newShape);
			entity.SetVelocity(newVelocity);

			return true;
		}

	}*/
	

	return m_pPlatforms->CheckWallHit(entity);
}
bool Level::HitPlatformLedge(Entity& entity) const
{
	return m_pPlatforms->HitLedge(entity);
}

bool Level::AreWallsGone() const
{
	return m_AreWallsGone;
}

void Level::DeleteWall(float elapsedSec, Entity& entity)
{
	float collisionTimer{};
	const Rectf entityShape{ entity.GetShape() };
	Vector2f newVelocity{ entity.GetVelocity() };

	collisionTimer += elapsedSec;


	for (size_t index{}; index < m_pWalls.size(); ++index)
	{
		const float attackVelocity{ -90.f };

		if (m_pWalls[index] && entityShape.left + entityShape.width >= m_pWalls[index]->GetShape().left)
		{
			delete m_pWalls[index];
			m_pWalls[index] = nullptr;

			m_WallCount--;

			if (collisionTimer >= 1.f)
			{
				entity.GetSprite()->PlayAnimation("Attack");
				newVelocity.x = attackVelocity;
				collisionTimer = 0;
			}
		}
	}

	if (m_WallCount == 0)
	{
		newVelocity.x = 1000;
		entityShape.left > 10000.f ? entity.SetVisible(false) : entity.SetVisible(true);
		m_AreWallsGone = true;
	}

	entity.SetVelocity(newVelocity);
}

Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}
std::vector<std::vector<Point2f>> Level::GetCheckpointWalls() const
{
	return m_CheckPointWalls;
}
//void Level::DrawBezier() const
//{
//	Point2f p0{2952.f, 540.f};
//	Point2f p1{3650.f, -450.f};
//	Point2f p2{3454.f, 714.f};
//	Point2f p3{3654.f, 96.f};
//
//	std::vector < Point2f> points;
//	utils::SetColor(Color4f{ 0.22f, 0.33f, 0.11f, 1.f });
//
//	for (float step{}; step <= 1.0f; step += 0.01f)
//	{
//		Point2f P01{ Lerp(p0,p1,step) };
//		Point2f P12{ Lerp(p1,p2,step) };
//		Point2f P23{ Lerp(p2,p3,step) };
//
//		Point2f U1{ Lerp(P01,P12,step) };
//		Point2f U2{ Lerp(P12,P23,step) };
//		
//		points.push_back(Lerp(U1, U2, step));
//
//		//utils::FillEllipse(P, 2.f, 2.f);
//	}
//
//	for (size_t index{ 1 }; index < points.size(); ++index)
//	{
//		utils::DrawLine(points[index - 1], points[index],5.f);
//	}
//	
//
//	/*std::cout << Vector2f(P) << std::endl;*/
//
//
//
//}
std::vector<Wall*> Level::GetWalls() const
{
	return m_pWalls;
}
#pragma endregion
#pragma region Cleanup
void Level::CleanUp()
{
	Level::DeleteStageTextures();
	Level::DeletePlatforms();
	Level::DeleteStartSign();
	Level::DeleteSpawnPoints();
	Level::DeleteMovingWater();
	Level::DeleteWaterfall();
	Level::DeleteFoam();
	Level::DeleteWalls();
}
void Level::DeleteStageTextures()
{
	delete m_pStage;
	m_pStage = nullptr;

	delete m_pForeGround;
	m_pForeGround = nullptr;
}
void Level::DeletePlatforms()
{
	delete m_pPlatforms;
	m_pPlatforms = nullptr;
}
void Level::DeleteStartSign()
{
	delete m_pStartSign;
	m_pStartSign = nullptr;
}

void Level::DeleteSpawnPoints()
{
	delete m_pSpawnPoints;
	m_pSpawnPoints = nullptr;
}
void Level::DeleteMovingWater()
{
	for (AnimatedSprite* pSprite : m_pMovingWaterTop)
	{
		if (pSprite)
		{
			delete pSprite;
			pSprite = nullptr;
		}
	}
	for (AnimatedSprite* sprite : m_pMovingWaterBottom)
	{
		if (sprite)
		{
			delete sprite;
			sprite = nullptr;
		}
	}

	m_pMovingWaterTop.clear();
	m_pMovingWaterBottom.clear();

}
void Level::DeleteWaterfall()
{
	delete m_pWaterfall;
	m_pWaterfall = nullptr;
}
void Level::DeleteFoam()
{
	delete m_pBottomFoam;
	m_pBottomFoam = nullptr;

	delete m_pTopFoam;
	m_pTopFoam = nullptr;
}
void Level::DeleteWalls()
{
	for (Wall* pWall : m_pWalls)
	{
		if (pWall)
		{
			delete pWall;
			pWall = nullptr;
		}
	}
}
#pragma endregion