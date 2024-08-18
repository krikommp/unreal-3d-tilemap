#pragma once

namespace T3D {
	enum class EMapBuilderMode : uint8
	{
		NONE = 0,
		View,
		Block,
		Mesh,
		AIPawn,
		PlayerPawn,
		PlayerStart,
	};

	enum class EMapBuilderViewSubMode : uint8
	{
		View = 0,
	};

	enum class EMapBuilderBlockSubMode : uint8
	{
		Add,
		Remove,
	};

	enum class EMapBuilderMeshSubMode : uint8
	{
		Spawn,
		Remove,
		Select,
	};

	enum class EMapBuilderAIPawnMode : uint8
	{
		Spawn,
		Remove,
	};

	enum class EMapBuilderPlayerPawnMode : uint8
	{
		Spawn,
		Remove,
	};

	enum class EMapBuilderPlayerStartMode : uint8
	{
		Spawn,
		Remove,
	};
}