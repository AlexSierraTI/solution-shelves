#pragma once

#include "Engine/Core.h"
#include "Engine/Events/Event.h"

namespace SolutionShelves
{
	class SOLUTION_SHELVES_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};
}

