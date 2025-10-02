#include <sstream>
#include "GameState.hpp"
#include "DEFINITIONS.hpp"
#include "GameOverState.hpp"

#include <iostream>

namespace PixelPanic
{
	GameState::GameState(GameDataRef data) : _data(data)
	{
	}

	void GameState::Init()
	{
		if (!this->_hitSoundBuffer.loadFromFile(HIT_SOUND_FILEPATH))
		{
			std::cout << "Error loading Hit Sound Effect" << std::endl;
		}

		if (!this->_wingSoundBuffer.loadFromFile(WING_SOUND_FILEPATH))
		{
			std::cout << "Error loading Wing Sound Effect" << std::endl;
		}

		if (!this->_pointSoundBuffer.loadFromFile(POINT_SOUND_FILEPATH))
		{
			std::cout << "Error loading Point Sound Effect" << std::endl;
		}

		this->_hitSound = std::make_unique<sf::Sound>(this->_hitSoundBuffer);
		this->_wingSound = std::make_unique<sf::Sound>(this->_wingSoundBuffer);
		this->_pointSound = std::make_unique<sf::Sound>(this->_pointSoundBuffer);

		this->_data->assets.LoadTexture("Game Background", GAME_BACKGROUND_FILEPATH);
		this->_data->assets.LoadTexture("Pipe Up", PIPE_UP_FILEPATH);
		this->_data->assets.LoadTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		this->_data->assets.LoadTexture("Scoring Pipe", SCORING_PIPE_FILEPATH);
		this->_data->assets.LoadTexture("Land", LAND_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 1", BIRD_FRAME_1_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 2", BIRD_FRAME_2_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 3", BIRD_FRAME_3_FILEPATH);
		this->_data->assets.LoadTexture("Bird Frame 4", BIRD_FRAME_4_FILEPATH);
		this->_data->assets.LoadFont("Flappy Font", FLAPPY_FONT_FILEPATH);

		pipe = new Pipe(this->_data);
		land = new Land(this->_data);
		bird = new Bird(this->_data);
		flash = new Flash(this->_data);
		hud = new HUD(this->_data);

		this->_background = std::make_unique<sf::Sprite>(this->_data->assets.GetTexture("Game Background"));

		this->_score = 0;

		hud->UpdateScore(this->_score);

		this->_gameState = GameStates::eReady;
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
				if (this->_gameState != GameStates::eGameOver)
				{
					this->_gameState = GameStates::ePlaying;

					bird->Tap();

					this->_wingSound->play();
				}
			}
		}
	}

	void GameState::Update(float dt)
	{
		if (this->_gameState != GameStates::eGameOver)
		{
			bird->Animate(dt);
			land->MoveLand(dt);
		}

		if (this->_gameState == GameStates::ePlaying)
		{
			pipe->MovePipes(dt);

			if (clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
			{
				pipe->RandomizePipeOffset();

				pipe->SpawnInvisiblePipe();
				pipe->SpawnBottomPipe();
				pipe->SpawnTopPipe();
				pipe->SpawnScoringPipe();

				clock.restart();
			}

			bird->Update(dt);

			std::vector<sf::Sprite> landSprites = land->GetSprites();
			for (int i = 0; i < landSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.7f, landSprites.at(i), 1.0f))
				{
					this->_gameState = GameStates::eGameOver;

					clock.restart();

					this->_hitSound->play();
				}
			}

			std::vector<sf::Sprite> pipeSprites = pipe->GetSprites();
			for (int i = 0; i < pipeSprites.size(); i++)
			{
				if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, pipeSprites.at(i), 1.0f))
				{
					this->_gameState = GameStates::eGameOver;

					clock.restart();

					this->_hitSound->play();
				}
			}

			if (this->_gameState == GameStates::ePlaying)
			{
				std::vector<sf::Sprite>& scoringSprites = pipe->GetScoringSprites();
				for (int i = 0; i < scoringSprites.size(); i++)
				{
					if (collision.CheckSpriteCollision(bird->GetSprite(), 0.625f, scoringSprites.at(i), 1.0f))
					{
						this->_score++;

						hud->UpdateScore(this->_score);

						scoringSprites.erase(scoringSprites.begin() + i);

						this->_pointSound->play();
					}
				}
			}
		}

		if (this->_gameState == GameStates::eGameOver)
		{
			this->flash->Show(dt);

			if (clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
			{
				this->_data->machine.AddState(StateRef(new GameOverState(this->_data, this->_score)), true);
			}
		}
	}

	void GameState::Draw(float dt)
	{
		this->_data->window.clear();

		this->_data->window.draw(*_background);

		pipe->DrawPipes();
		land->DrawLand();
		bird->Draw();
		flash->Draw();
		hud->Draw();

		this->_data->window.display();
	}
}