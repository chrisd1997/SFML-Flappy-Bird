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
		this->_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		this->_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		this->_data->assets.LoadTexture("Land", LAND_FILEPATH);

		pipe = new Pipe(this->_data);
		land = new Land(this->_data);

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

			if (this->_data->input.IsSpriteClicked(*this->_background, sf::Mouse::Button::Left, this->_data->window))
			{

			}
		}
	}

	void GameState::Update(float dt)
	{
		pipe->RandomizePipeOffset();

		pipe->MovePipes(dt);
		land->MoveLand(dt);

		if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
		{
			pipe->SpawnInvisiblePipe();
			pipe->SpawnBottomPipe();
			pipe->SpawnTopPipe();

			clock.restart();
		}
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(*_background);

		pipe->DrawPipes();
		land->DrawLand();

		this->_data->window.display();
	}
}