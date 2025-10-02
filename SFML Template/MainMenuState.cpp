#include <sstream>
#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace PixelPanic
{
	MainMenuState::MainMenuState(GameDataRef data) : _data(data)
	{

	}

	void MainMenuState::Init()
	{
		this->_data->assets.LoadTexture(MAIN_MENU_BACKGROUND_NAME, MAIN_MENU_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture(GAME_TITLE_NAME, GAME_TITLE_FILEPATH);
		this->_data->assets.LoadTexture(PLAY_BUTTON_NAME, PLAY_BUTTON_FILEPATH);

		this->_background = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(MAIN_MENU_BACKGROUND_NAME));
		this->_title = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(GAME_TITLE_NAME));
		this->_playButton = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(PLAY_BUTTON_NAME));

		const float titlePosX = (SCREEN_WIDTH / 2) - (this->_title->getGlobalBounds().size.x / 2);
		const float titlePosY = this->_title->getGlobalBounds().size.y / 2;
		this->_title->setPosition({ titlePosX, titlePosY });

		const float playButtonPosX = (SCREEN_WIDTH / 2) - (this->_playButton->getGlobalBounds().size.x / 2);
		const float playButtonPosY = (SCREEN_HEIGHT / 2) - (this->_playButton->getGlobalBounds().size.y / 2);
		this->_playButton->setPosition({ playButtonPosX, playButtonPosY });
	}

	void MainMenuState::HandleInput()
	{
		while (std::optional event = this->_data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(*this->_playButton, sf::Mouse::Button::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new GameState(this->_data)), true);
			}
		}
	}

	void MainMenuState::Update(float dt)
	{

	}

	void MainMenuState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(*_background);
		this->_data->window.draw(*_title);
		this->_data->window.draw(*_playButton);

		this->_data->window.display();
	}
}