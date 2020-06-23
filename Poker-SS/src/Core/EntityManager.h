#pragma once

#include "Base.h"
#include "Entities/Entity.h"

namespace PokerSS
{
	class EntityManager
	{
	public:
		EntityManager();
		~EntityManager();

		void PushEntity(SolutionShelves::Ref<Entity> entity);
		void PopEntity(SolutionShelves::Ref<Entity> entity);

		uint32_t GetEntitiesCount() const { return m_EntitiesCount; }

		SolutionShelves::Ref<Entity> GetEntity(uint32_t entityID) const { return m_EntityList.at(entityID); }

		void RenderEntities();
		void UpdateEntities(SolutionShelves::Timestep ts);
		void ImGuiRender();
	private:
		std::unordered_map<uint32_t, SolutionShelves::Ref<Entity>> m_EntityList;
		uint32_t m_EntitiesCount;
	};
}
