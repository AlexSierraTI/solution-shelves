#include "sspch.h"
#include "Label.h"

namespace SolutionShelves
{
	Label::Label(const std::string& text, const glm::vec3& position, const glm::vec4& color)
		: m_Text(text), m_Position(position), m_Color(color)
	{
	}

	Label::~Label()
	{
	}

}