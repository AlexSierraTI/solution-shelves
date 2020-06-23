#pragma once

#include <SolutionShelves.h>

namespace PokerSS
{
	enum class Orientation
	{
		LEFT, RIGHT, DOWN, UP
	};

	struct PlayerData
	{
		glm::vec2 Position = { 0.0f, 0.0f };
		Orientation Direction = Orientation::UP;

		PlayerData(glm::vec2 pos, Orientation dir)
			: Position(pos), Direction(dir)
		{
		}
	};
}
