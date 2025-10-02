#pragma once

#include <SFML/Graphics.hpp>
#include "State.hpp"
#include "Game.hpp"

namespace PixelPanic
{
	class GameOverState : public State
	{
	public:
		GameOverState(GameDataRef data, unsigned int score);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		std::unique_ptr<sf::Sprite> _background;
		std::unique_ptr<sf::Sprite> _gameOverTitle;
		std::unique_ptr<sf::Sprite> _gameOverContainer;
		std::unique_ptr<sf::Sprite> _retryButton;
		std::unique_ptr<sf::Sprite> _medal;

		std::unique_ptr<sf::Text> _scoreText;
		std::unique_ptr<sf::Text> _highScoreText;

		unsigned int _score;
		unsigned int _highScore;
	};
}