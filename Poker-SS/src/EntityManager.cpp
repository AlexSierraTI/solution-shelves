#include "EntityManager.h"

namespace PokerSS
{
	EntityManager::EntityManager()
		: m_EntitiesCount(0)
	{
	}

	EntityManager::~EntityManager()
	{
		m_EntityList.clear();
	}

	void EntityManager::PushEntity(SolutionShelves::Ref<Entity> entity)
	{
		entity->SetEntityID(m_EntitiesCount);
		m_EntityList[m_EntitiesCount] = entity;
		m_EntitiesCount++;
	}

	void EntityManager::PopEntity(SolutionShelves::Ref<Entity> entity)
	{
		m_EntityList.erase(entity->GetEntityID());
		m_EntitiesCount--;
	}

	void EntityManager::RenderEntities()
	{
		for (auto& it : m_EntityList)
			if (it.second->ShouldRender()) it.second->OnRender();
	}

	void EntityManager::UpdateEntities(SolutionShelves::Timestep ts)
	{
		for (auto& it : m_EntityList)
			it.second->OnUpdate(ts);
	}

	void EntityManager::ImGuiRender()
	{
		for (auto& it : m_EntityList)
			it.second->OnImGuiRender();
	}

}
