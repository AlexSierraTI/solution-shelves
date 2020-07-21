#pragma once

#include "entt.hpp"

#include "Engine/Core/Timestep.h"

namespace SolutionShelves
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		entt::entity CreateEntity();

		// TEMP
		entt::registry& Reg() { return m_Registry; }

		void OnUpdate(Timestep ts);
	private:
		entt::registry m_Registry;
	};
}
