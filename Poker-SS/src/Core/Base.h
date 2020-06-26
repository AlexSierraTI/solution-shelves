#pragma once

#include <SolutionShelves.h>

namespace PokerSS
{
	enum class Orientation
	{
		LEFT, RIGHT, DOWN, UP
	};

	struct PlayerData
	{
		glm::vec2 Position = { 0.0f, 0.0f };
		Orientation Direction = Orientation::UP;

		PlayerData(glm::vec2 pos, Orientation dir)
			: Position(pos), Direction(dir)
		{
		}
	};

	enum class Suit
	{
		Unknown, Clubs, Hearts, Spades, Diamonds
	};
	enum class FaceValue
	{
		Unknown, Deuce, Tray, Four, Five, Six, Seven, Eight, Nine, Ten, Jack, Queen, King, Ace
	};

	enum class CardBack
	{
		RedFlat, GreenFlat, GreenBorder,
		RedManySuitBorder, GreenManySuitBorder, BlueManySuitBorder,
		RedBorder, BlueFlat, BlueBorder,
		RedManySuits, GreenManySuits, BlueManySuits,
		Red4Suits, Green4Suits, Blue4Suits
	};

	struct SidePot
	{
		uint32_t Valor;
		uint32_t ValorAllIn;
		SidePot(uint32_t valor, uint32_t valorAllIn)
			: Valor(valor), ValorAllIn(valorAllIn)
		{
		}
	};

}
