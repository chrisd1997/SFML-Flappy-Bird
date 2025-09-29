#include <sstream>
#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace PixelPanic
{
	GameOverState::GameOverState(GameDataRef data) : _data(data)
	{

	}

	void GameOverState::Init()
	{
		this->_data->assets.LoadTexture("Game Over Background", GAME_OVER_BACKGROUND_FILEPATH);

		this->_background = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture("Game Over Background"));
	}

	void GameOverState::HandleInput()
	{
		while (std::optional event = this->_data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				this->_data->window.close();
			}
		}
	}

	void GameOverState::Update(float dt)
	{

	}

	void GameOverState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(*_background);

		this->_data->window.display();
	}
}