#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace PixelPanic
{
	class MainMenuState : public State
	{
	public:
		MainMenuState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		std::unique_ptr<sf::Sprite> _background;
		std::unique_ptr<sf::Sprite> _title;
		std::unique_ptr<sf::Sprite> _playButton;
	};
}