#include <sstream>
#include "GameOverState.hpp"
#include "DEFINITIONS.hpp"
#include "GameState.hpp"

#include <iostream>
#include <fstream>

namespace PixelPanic
{
	GameOverState::GameOverState(GameDataRef data, unsigned int score) : _data(data), _score(score)
	{

	}

	void GameOverState::Init()
	{
		std::fstream readFile;
		readFile.open(HIGHSCORE_FILEPATH);

		if (readFile.is_open())
		{
			while (!readFile.eof())
			{
				readFile >> this->_highScore;
			}
		}

		readFile.close();

		std::ofstream writeFile(HIGHSCORE_FILEPATH);

		if (writeFile.is_open())
		{
			if (this->_score > this->_highScore)
			{
				this->_highScore = this->_score;
			}

			writeFile << this->_highScore;
		}

		writeFile.close();

		this->_data->assets.LoadTexture(GAME_OVER_BACKGROUND_NAME, GAME_OVER_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture(GAME_OVER_TITLE_NAME, GAME_OVER_TITLE_FILEPATH);
		this->_data->assets.LoadTexture(GAME_OVER_BODY_NAME, GAME_OVER_BODY_FILEPATH);

		this->_data->assets.LoadTexture(BRONZE_MEDAL_NAME, BRONZE_MEDAL_FILEPATH);
		this->_data->assets.LoadTexture(SILVER_MEDAL_NAME, SILVER_MEDAL_FILEPATH);
		this->_data->assets.LoadTexture(GOLD_MEDAL_NAME, GOLD_MEDAL_FILEPATH);
		this->_data->assets.LoadTexture(PLATINUM_MEDAL_NAME, PLATINUM_MEDAL_FILEPATH);

		this->_background = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(GAME_OVER_BACKGROUND_NAME));
		this->_gameOverTitle = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(GAME_OVER_TITLE_NAME));
		this->_gameOverContainer = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(GAME_OVER_BODY_NAME));
		this->_retryButton = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(PLAY_BUTTON_NAME));

		this->_gameOverContainer->setPosition({ (float)(this->_data->window.getSize().x / 2) - (float)(this->_gameOverContainer->getGlobalBounds().size.x / 2), (float)(this->_data->window.getSize().y / 2) - (float)(this->_gameOverContainer->getGlobalBounds().size.y / 2) });
		this->_gameOverTitle->setPosition({ (float)(this->_data->window.getSize().x / 2) - (float)(this->_gameOverTitle->getGlobalBounds().size.x / 2), (float)this->_gameOverContainer->getPosition().y - (float)(this->_gameOverTitle->getGlobalBounds().size.y * 1.2) });
		this->_retryButton->setPosition({ (float)(this->_data->window.getSize().x / 2) - (float)(this->_retryButton->getGlobalBounds().size.x / 2), (float)this->_gameOverContainer->getPosition().y + (float)this->_gameOverContainer->getGlobalBounds().size.y + (float)(this->_retryButton->getGlobalBounds().size.y * 0.2) });

		this->_scoreText = std::make_unique<sf::Text>(this->_data->assets.GetFont(FLAPPY_FONT_NAME));
		this->_scoreText->setString(std::to_string(this->_score));
		this->_scoreText->setCharacterSize(56);
		this->_scoreText->setFillColor(sf::Color::White);
		this->_scoreText->setOrigin({ (float)this->_scoreText->getGlobalBounds().size.x / 2, (float)this->_scoreText->getGlobalBounds().size.y / 2 });
		this->_scoreText->setPosition({ (float)(this->_data->window.getSize().x / 10 * 7.25), (float)(this->_data->window.getSize().y / 2.15) });

		this->_highScoreText = std::make_unique<sf::Text>(this->_data->assets.GetFont(FLAPPY_FONT_NAME));
		this->_highScoreText->setString(std::to_string(this->_highScore));
		this->_highScoreText->setCharacterSize(56);
		this->_highScoreText->setFillColor(sf::Color::White);
		this->_highScoreText->setOrigin({ (float)this->_highScoreText->getGlobalBounds().size.x / 2, (float)this->_highScoreText->getGlobalBounds().size.y / 2 });
		this->_highScoreText->setPosition({ (float)(this->_data->window.getSize().x / 10 * 7.25), (float)(this->_data->window.getSize().y / 1.78) });

		if (this->_score >= PLATINUM_MEDAL_SCORE)
		{
			this->_medal = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(PLATINUM_MEDAL_NAME));
		}
		else if (this->_score >= GOLD_MEDAL_SCORE)
		{
			this->_medal = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(GOLD_MEDAL_NAME));
		}
		else if (this->_score >= SILVER_MEDAL_SCORE)
		{
			this->_medal = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(SILVER_MEDAL_NAME));
		}
		else
		{
			this->_medal = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture(BRONZE_MEDAL_NAME));
		}

		this->_medal->setPosition({ 175.0f, 465.0f });
	}

	void GameOverState::HandleInput()
	{
		while (std::optional event = this->_data->window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				this->_data->window.close();
			}

			if (this->_data->input.IsSpriteClicked(*this->_retryButton, sf::Mouse::Button::Left, this->_data->window))
			{
				this->_data->machine.AddState(StateRef(new GameState(this->_data)));
			}
		}
	}

	void GameOverState::Update(float dt)
	{

	}

	void GameOverState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(*this->_background);
		this->_data->window.draw(*this->_gameOverContainer);
		this->_data->window.draw(*this->_gameOverTitle);
		this->_data->window.draw(*this->_retryButton);
		this->_data->window.draw(*this->_scoreText);
		this->_data->window.draw(*this->_highScoreText);
		this->_data->window.draw(*this->_medal);

		this->_data->window.display();
	}
}