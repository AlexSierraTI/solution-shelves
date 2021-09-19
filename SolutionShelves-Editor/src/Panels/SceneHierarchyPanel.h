#pragma once

#include "Engine/Core/Base.h"
#include "Engine/Scene/Scene.h"
#include "Engine/Scene/Entity.h"

namespace SolutionShelves
{
	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();

		void SetSelectedEntity(Entity entity) { m_SelectionContext = entity; }
		Entity GetSelectedEntity() const { return m_SelectionContext; }
	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}
