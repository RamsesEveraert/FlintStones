#include "pch.h"
#include "PlatformManager.h"
#include "Entity.h"
#include "Logs.h"
#include "StageBlocks.h"
#include "utils.h"
#include "SVGParser.h"

PlatformManager::PlatformManager()
	: m_VerticesPlatforms{ }
	, m_AmountFloorBlocks {20}
{
	PlatformManager::CreatePlatformVertices();
	PlatformManager::CreateLogs();
	PlatformManager::CreateFloorBlocks();
}

PlatformManager::~PlatformManager()
{
	PlatformManager::DeleteLogs();
	PlatformManager::DeleteFloorBlocks();
}

#pragma region Initialization
void PlatformManager::CreatePlatformVertices()
{
	std::string stageFile{ "Resources/Stage/platforms.svg" };
	SVGParser::GetVerticesFromSvgFile(stageFile, m_VerticesPlatforms);
}
void PlatformManager::CreateLogs()
{
	const float slowSpeed{ 8.f };
	const float mediumSpeed{ 15.f };
	const float fastSpeed{ 25.f };

	const int amountLogs{ 4 };


	for (size_t log{ }; log <= amountLogs - 1; ++log)
	{
		const Vector2f startPosLog{ 6200.f , utils::GetRandomNumber(444, 487, true) };
		const Vector2f distanceLogs{ 35, utils::GetRandomNumber(70, 90, true) };

		Rectf shapeLog{ startPosLog.x, startPosLog.y, 48.f, 14.f };

		shapeLog.bottom = startPosLog.y - log * (shapeLog.height + distanceLogs.y);

		m_pLogs.push_back(new Logs(shapeLog, slowSpeed));

		shapeLog.left += (shapeLog.width + distanceLogs.x);

		m_pLogs.push_back(new Logs(shapeLog, fastSpeed));

		shapeLog.left += (shapeLog.width + distanceLogs.x);

		m_pLogs.push_back(new Logs(shapeLog, mediumSpeed));
	}
}
void PlatformManager::CreateFloorBlocks()
{
	for (int index{}; index < m_AmountFloorBlocks; ++index)
	{
		const float width{ 70.f };
		const float height{ 30.f };
		const Point2f startPos{ 4605.f, 111.f };

		m_pFloorBlocks.push_back(new StageBlocks(Rectf{ startPos.x + index * width, startPos.y, width, height }));
	}

}
#pragma endregion 
#pragma region GeneralFunctions
void PlatformManager::DrawLogs() const
{
	for (Logs* pLogs : m_pLogs)
	{
		if (pLogs) pLogs->Draw();
	}
}
void PlatformManager::DrawFloorBlocks() const
{
	for (StageBlocks* pFloor : m_pFloorBlocks)
	{
		if (pFloor)	pFloor->Draw();
	}
}

void PlatformManager::Update(float elapsedSec)
{
	PlatformManager::UpdateLogs(elapsedSec);
	PlatformManager::UpdateFloorBlocks(elapsedSec);
}
void PlatformManager::UpdateLogs(float elapsedSec)
{
	for (Logs* pLogs : m_pLogs)
	{
		pLogs->Update(elapsedSec);
	}
}
void PlatformManager::UpdateFloorBlocks(float elapsedSec)
{
	for (StageBlocks* pFloor : m_pFloorBlocks)
	{
		if (pFloor)
			pFloor->Update(elapsedSec);
	}
}
#pragma endregion 
#pragma region Checks
void PlatformManager::HandleCollision(Entity& entity) const
{
	PlatformManager::IsOnGround(entity);
}
bool PlatformManager::IsOnGround(Entity& entity) const
{
	const Rectf entityShape{ entity.GetShape() };

	const float platformHeight{ 23.f };
	const float rayOffset{ 10.f };

	Point2f startRay{ entityShape.left + 0.5f * entityShape.width, entityShape.bottom + rayOffset };
	Point2f endRay{ entityShape.left + 0.5f * entityShape.width, entityShape.bottom - 1.f };

	utils::HitInfo hitInfo;

	for (const std::vector<Point2f>& surface : m_VerticesPlatforms)
	{
		if (entity.GetVelocity().y <= 0 && utils::Raycast(surface, startRay, endRay, hitInfo))
		{
			Rectf newShape = entityShape;
			Vector2f newVelocity = entity.GetVelocity();

			newShape.bottom = hitInfo.intersectPoint.y;
			newVelocity.y = 0;

			entity.SetShape(newShape);
			entity.SetVelocity(newVelocity);

			return true;
		}
	}

	// waterfall logs

	for (Logs* pLogs : m_pLogs)
	{
		if (pLogs)
		{
			const Rectf shapeLogs{ pLogs->GetShape() };

			Point2f leftTopCorner{ shapeLogs.left, shapeLogs.bottom + shapeLogs.height };
			Point2f rightTopCorner{ shapeLogs.left + shapeLogs.width, shapeLogs.bottom + shapeLogs.height };

			std::vector<std::vector<Point2f>> surfaceLogs{ std::vector<Point2f>{leftTopCorner, rightTopCorner} };

			for (const std::vector<Point2f>& surface : surfaceLogs)
			{
				if (entity.GetVelocity().y <= 0 && utils::Raycast(surface, startRay, endRay, hitInfo))
				{
					Rectf newShape{ entity.GetShape() };
					Vector2f newVelocity{ entity.GetVelocity() };

					newShape.bottom = hitInfo.intersectPoint.y;
					newVelocity.y = 0;

					entity.SetShape(newShape);
					entity.SetVelocity(newVelocity);

					return true;
				}
			}

		}

	}

	// destroyable floor

	for (StageBlocks* pFloor : m_pFloorBlocks)
	{
		if (pFloor)
		{
			const Rectf shapeFloorBlock{ pFloor->GetShape() };
			if (utils::IsOverlapping(entity.GetHitbox(), shapeFloorBlock))
			{
				Rectf newShape{ entity.GetShape() };
				Vector2f newVelocity = entity.GetVelocity();

				newShape.bottom = shapeFloorBlock.bottom + shapeFloorBlock.height;
				newVelocity.y = 0;

				entity.SetShape(newShape);
				entity.SetVelocity(newVelocity);

				return true;
			}

		}

	}


	return false;
}
bool PlatformManager::CheckWallHit(Entity& entity) const
{
	const Rectf entityShape{ entity.GetShape() };
	const float rayLength{ entity.IsFacingLeft() ? 0.2f * entityShape.width : 0.75f * entityShape.width };

	Point2f startRay{ entityShape.left + 0.5f * entityShape.width,entityShape.bottom + 0.5f * entityShape.height };
	Point2f endRay{ entityShape.left + rayLength, entityShape.bottom + 0.5f * entityShape.height };

	utils::HitInfo hitInfo;

	for (const std::vector<Point2f>& surface : m_VerticesPlatforms)
	{
		if (utils::Raycast(surface, startRay, endRay, hitInfo))
		{
			Rectf newShape{ entityShape };
			Vector2f newVelocity{ entity.GetVelocity() };

			(entity.IsFacingLeft())
				? newShape.left = hitInfo.intersectPoint.x - 0.2f * entityShape.width
				: newShape.left = hitInfo.intersectPoint.x - 0.75f * entityShape.width;
			newVelocity.x = 0;

			entity.SetShape(newShape);
			entity.SetVelocity(newVelocity);

			return true;
		}
	}
	return false;
}
bool PlatformManager::HitLedge(Entity& entity) const
{
	const Rectf entityShape{ entity.GetShape() };

	Rectf newShape = entityShape;
	Vector2f newVelocity = entity.GetVelocity();

	const float ledgeOffset{ 8.f };
	const Rectf hitBox{ entityShape.left + 0.25f * entityShape.width, entityShape.bottom + 0.75f * entityShape.height, 0.5f * entityShape.width, 0.25f * entityShape.height };

	for (const std::vector<Point2f>& platform : m_VerticesPlatforms)
	{
		if (entity.GetVelocity().y < 0)
		{
			const Point2f* pLeftPoint{};
			const Point2f* pRightPoint{};

			for (const Point2f& point : platform)
			{
				if (pLeftPoint == nullptr || point.x < pLeftPoint->x) pLeftPoint = &point;			// meest linkse punt zoeken
				if (pRightPoint == nullptr || point.x > pRightPoint->x) pRightPoint = &point;		// meest rechtse punt zoeken
			}

			if (pLeftPoint && !entity.IsFacingLeft() && utils::IsPointInRect(*pLeftPoint, hitBox))
			{
				newVelocity.y = 0;
				newShape.left = pLeftPoint->x + ledgeOffset - 0.75f * entityShape.width;
				newShape.bottom = pLeftPoint->y - entityShape.height;

				entity.SetShape(newShape);
				entity.SetVelocity(newVelocity);

				return true;
			}
			else if (pRightPoint && entity.IsFacingLeft() && utils::IsPointInRect(*pRightPoint, hitBox))
			{

				newVelocity.y = 0;
				newShape.left = pRightPoint->x + ledgeOffset - 0.75f * entity.GetShape().width;
				newShape.bottom = pRightPoint->y - entity.GetShape().height;

				entity.SetShape(newShape);
				entity.SetVelocity(newVelocity);

				return true;
			}
		}
	}

	// Waterfall Logs

	for (Logs* pLogs : m_pLogs)
	{
		const Rectf shapeLogs{ pLogs->GetShape() };
		if (pLogs)
		{
			const float heightBridge{ 150.f };

			Point2f leftTopCorner{ shapeLogs.left, shapeLogs.bottom + shapeLogs.height };
			Point2f rightTopCorner{ shapeLogs.left + shapeLogs.width, shapeLogs.bottom + shapeLogs.height };

			if (!entity.IsFacingLeft() && utils::IsPointInRect(leftTopCorner, hitBox))
			{
				entity.SetMovingLog(pLogs);


				if (entityShape.bottom <= heightBridge)
				{
					entity.SetMovingLog(nullptr);
					return false;
				}

				newVelocity.y = 0;
				newShape.left = leftTopCorner.x + ledgeOffset - 0.75f * entityShape.width;
				newShape.bottom = leftTopCorner.y - entityShape.height;

				entity.SetShape(newShape);
				entity.SetVelocity(newVelocity);


				return true;
			}
			else if (entity.IsFacingLeft() && utils::IsPointInRect(rightTopCorner, entityShape))
			{
				entity.SetMovingLog(pLogs);

				newVelocity.y = 0;
				newShape.left = rightTopCorner.x + ledgeOffset - 0.75f * entityShape.width;
				newShape.bottom = rightTopCorner.y - entityShape.height;

				entity.SetShape(newShape);
				entity.SetVelocity(newVelocity);

				return true;
			}

		}

	}
	entity.SetMovingLog(nullptr);
	return false;

}
#pragma endregion 
#pragma region CleanUp
void PlatformManager::DeleteLogs()
{
	for (Logs* pLogs : m_pLogs)
	{
		if (pLogs)
		{
			delete pLogs;
			pLogs = nullptr;
		}
	}
}
void PlatformManager::DeleteFloorBlocks()
{
	for (StageBlocks* pFloor : m_pFloorBlocks)
	{
		if (pFloor)
		{
			delete pFloor;
			pFloor = nullptr;
		}
	}
}
#pragma endregion 

//		EXTRA: timer maken voor nieuwe log + 3d effect log achter schuimlaad en dan ervoor eens naar beneden gaat voor de schuimlaag