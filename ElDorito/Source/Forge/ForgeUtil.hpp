#pragma once

#include "../Blam/BlamTypes.hpp"
#include "../Blam/Math/RealMatrix4x3.hpp"
#include "../Blam/Math/RealVector3D.hpp"

namespace Forge
{
	struct ZoneShape
	{
		int32_t Shape;
		float Width;
		float Depth;
		float Top;
		float Bottom;
		Blam::Math::RealMatrix4x3 Transform;
		float BoundingRadius;
		uint32_t Unknown4C;
	};
	static_assert(sizeof(ZoneShape) == 0x50, "Invalid ZoneShape size");

	struct SandboxGlobals
	{
		uint32_t Unknown00;
		uint32_t Unknown04;
		uint16_t PlayersInMonitorModeBitSet;
		uint16_t Unknown06;
		uint32_t HeldObjects[16];
		float HeldObjectDistances[16];
		Blam::Math::RealVector3D CrosshairPoints[16];
		Blam::Math::RealVector3D CrosshairIntersectNormals[16];
		Blam::Math::RealVector3D CrosshairDirections[16];
		uint32_t CrosshairObjects[16];
		uint8_t UnknownE49c[0x43c];
	};
	static_assert(sizeof(SandboxGlobals) == 0x748, "Invalid SandboxGlobals size");

	const auto GetObjectZoneShape = (void(__cdecl *)(uint32_t objectIndex, ZoneShape* zoneShape, int a3))(0xBA0AD0);
	const auto PointIntersectsZone = (bool(__cdecl*)(const Blam::Math::RealVector3D* point, const ZoneShape* zone))(0x00BA11F0);
	const auto GetObjectTransformationMatrix = (void(__cdecl*)(uint32_t objectIndex, Blam::Math::RealMatrix4x3* outMatrix))(0x00B2EC60);
	const auto GetObjectPosition = (void(*)(uint32_t objectIndex, Blam::Math::RealVector3D *position))(0xB2E5A0);
	const auto SpawnObject = (uint32_t(__thiscall *)(Blam::MapVariant* thisptr, uint32_t tagIndex, int a3, int16_t placementIndex,
		const Blam::Math::RealVector3D *position, const Blam::Math::RealVector3D *rightVec, const Blam::Math::RealVector3D *upVec, int16_t scnrPlacementBlockIndex,
		int objectType, const Blam::MapVariant::VariantProperties* variantProperties, uint16_t placementFlags))(0x00582110);
	const auto GetPlayerHoldingObject = (uint32_t(__cdecl*)(int objectIndex))(0x0059BB90);
	const auto GetEditorModeState = (bool(__cdecl *)(uint32_t playerIndex, uint32_t* heldObjectIndex, uint32_t* objectIndexUnderCrosshair))(0x59A6F0);
	const auto GetSandboxGlobals = (SandboxGlobals&(*)())(0x0059BC10);

	Blam::MapVariant* GetMapVariant();

	struct AABB { float MinX, MaxX, MinY, MaxY, MinZ, MaxZ; };
	bool CalculateObjectBoundingBox(uint32_t objectIndex, AABB* outBoundingBox);
	Blam::Math::RealVector3D GetClosestCardianalAxix(const Blam::Math::RealVector3D& v);
	void DeleteObject(uint16_t playerIndex, int16_t placementIndex);
	uint32_t CloneObject(uint32_t playerIndex, uint32_t objectIndex, float depth);
	void ThrowObject(uint32_t playerIndex, uint32_t objectIndex, float throwForce);
	void CanvasMap();

}