#include <sstream>
#include "SplashState.hpp"
#include "MainMenuState.hpp"
#include "DEFINITIONS.hpp"

#include <iostream>

namespace PixelPanic
{
	SplashState::SplashState(GameDataRef data) : _data(data)
	{

	}

	void SplashState::Init()
	{
		this->_data->assets.LoadTexture(SPLASH_SCENE_BACKGROUND_NAME, SPLASH_SCENE_BACKGROUND_FILEPATH);

		this->_background = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(SPLASH_SCENE_BACKGROUND_NAME));
	}

	void SplashState::HandleInput()
	{
		while (std::optional event = this->_data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				this->_data->window.close();
			}
		}
	}

	void SplashState::Update(float dt)
	{
		if (this->_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			this->_data->machine.AddState(StateRef(new MainMenuState(this->_data)), true);
		}
	}

	void SplashState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(*_background);

		this->_data->window.display();
	}
}