#pragma once

#include "Entities/Entity.h"

namespace PokerSS
{
	class OldWest : public Entity
	{
	public:

		OldWest();
		~OldWest();

		virtual void LoadAssets() override;

		virtual void OnUpdate(SolutionShelves::Timestep ts) override;
		virtual void OnRender() override;

		virtual void OnImGuiRender() override;
		
		const PlayerData& GetPlayerData(uint32_t pos);
		const glm::vec2& GetMapLayout() const { return m_MapLayoutSize; }
	private:
		SolutionShelves::Ref<SolutionShelves::Texture2D> m_LevelTexture;
		glm::vec2 m_LevelSize;
		std::vector<PlayerData> m_PlayersData;

		glm::vec2 m_MapLayoutSize;

		PlayerData m_DefaultPos;
			
	};
}
