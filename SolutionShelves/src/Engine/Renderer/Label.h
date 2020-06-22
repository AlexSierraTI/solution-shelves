#pragma once

#include <glm/glm.hpp>

namespace SolutionShelves
{
	class Label
	{
	public:
		Label(const std::string&, const glm::vec3& position, const glm::vec4& color);
		~Label();

	private:
		std::string m_Text;
		glm::vec3 m_Position;
		glm::vec4 m_Color;

		
	};
}

