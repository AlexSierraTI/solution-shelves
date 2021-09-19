#include "sspch.h"
#include "Engine/Scene/Entity.h"

namespace SolutionShelves
{
	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}
}
