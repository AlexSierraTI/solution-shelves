#pragma once

#include "entt.hpp"

namespace SolutionShelves
{
	class Scene
	{
	public:
		Scene();
		~Scene();
	private:
		entt::registry m_Registry;
	};
}
