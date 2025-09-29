#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace PixelPanic
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		std::unique_ptr<sf::Sprite> _background;
	};
}