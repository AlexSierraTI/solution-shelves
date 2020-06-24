#pragma once

#include "Entities/Entity.h"

namespace PokerSS
{
	class Level : public Entity
	{
	public:
		virtual PlayerData& GetPlayerData(uint32_t pos) = 0;
		virtual glm::vec2& GetMapLayout() = 0;

	};
}
