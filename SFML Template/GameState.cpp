#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace PixelPanic
{
	GameState::GameState(GameDataRef data) : _data(data)
	{

	}

	void GameState::Init()
	{
		this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);

		this->_background = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture("Game Background"));
	}

	void GameState::HandleInput()
	{
		while (std::optional event = this->_data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				this->_data->window.close();
			}
		}
	}

	void GameState::Update(float dt)
	{

	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(*_background);

		this->_data->window.display();
	}
}