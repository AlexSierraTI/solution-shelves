#include "EntityManager.h"

namespace PokerSS
{

	EntityManager* EntityManager::s_Instance = nullptr;

	EntityManager::EntityManager()
		: m_EntitiesCount(0), m_EntityNextID(0)
	{
	}

	EntityManager::~EntityManager()
	{
		m_EntityList.clear();
	}

	void EntityManager::PushEntity(SolutionShelves::Ref<Entity> entity)
	{
		m_EntityNextID++;
		entity->SetEntityID(m_EntityNextID);
		m_EntityList.push_back(entity);
		m_EntitiesCount++;
	}

	void EntityManager::PopEntity(SolutionShelves::Ref<Entity> entity)
	{
		uint32_t index = 0;
		for (auto& it : m_EntityList)
		{
			if (it->GetEntityID() == entity->GetEntityID())
			{
				m_EntityList.erase(m_EntityList.begin() + index);
				m_EntitiesCount--;
				break;
			}
			index++;
		}
	}

	void EntityManager::RenderEntities()
	{
		for (auto& it : m_EntityList)
			if (it->ShouldRender()) it->OnRender();
	}

	void EntityManager::UpdateEntities(SolutionShelves::Timestep ts)
	{
		for (auto& it : m_EntityList)
			it->OnUpdate(ts);
	}

	void EntityManager::ImGuiRender()
	{
		for (auto& it : m_EntityList)
			it->OnImGuiRender();
	}
	
}
