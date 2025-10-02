#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.hpp"
#include "Game.hpp"

namespace PixelPanic
{
	class HUD
	{
	public:
		HUD(GameDataRef data);
		~HUD();

		void Draw();
		void UpdateScore(unsigned int score);

	private:
		GameDataRef _data;

		std::unique_ptr<sf::Text> _scoreText;
	};
}