#pragma once

#include <SolutionShelves.h>

#include "ImGui/imgui.h"
#include <glm/gtc/type_ptr.hpp>

namespace PokerSS
{
	class Entity
	{
	public:
		virtual void LoadAssets() = 0;

		virtual void OnUpdate(SolutionShelves::Timestep ts) = 0;
		virtual void OnRender() = 0;

		virtual void OnImGuiRender() = 0;

		bool ShouldRender() const { return m_ShouldRender; }
		uint32_t GetEntityID() const { return m_EntityID; }
		void SetEntityID(uint32_t entityID) { m_EntityID = entityID; }

		void EnableRender() { m_ShouldRender = true; }
		void DisableRender() { m_ShouldRender = false; }
	private:
		uint32_t m_EntityID = 0;

		bool m_ShouldRender = false;
	};

}