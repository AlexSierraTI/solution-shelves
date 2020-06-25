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

		SolutionShelves::Ref<Entity> GetEntity(uint32_t entityID) const { return m_EntityList[entityID]; }

		void RenderEntities();
		void UpdateEntities(SolutionShelves::Timestep ts);
		void ImGuiRender();

		static EntityManager& Get() { return *s_Instance; }
		static void CreateInstance() { s_Instance = new EntityManager(); };
	private:
		std::vector<SolutionShelves::Ref<Entity>> m_EntityList;
		uint32_t m_EntitiesCount;
		uint32_t m_EntityNextID;

		static EntityManager* s_Instance;
	};

}
