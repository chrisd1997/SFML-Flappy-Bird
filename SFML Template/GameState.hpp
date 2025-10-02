#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.hpp"
#include "Game.hpp"
#include "Pipe.hpp"
#include "Land.hpp"
#include "Bird.hpp"
#include "Collision.hpp"
#include "Flash.hpp"
#include "HUD.hpp"

namespace PixelPanic
{
	class GameState : public State
	{
	public:
		GameState(GameDataRef data);

		void Init();

		void HandleInput();
		void Update(float dt);
		void Draw(float dt);

	private:
		GameDataRef _data;

		std::unique_ptr<sf::Sprite> _background;

		Pipe* pipe;
		Land* land;
		Bird* bird;
		Collision collision;
		Flash* flash;
		HUD* hud;

		sf::Clock clock;

		int _gameState;

		unsigned int _score;

		sf::SoundBuffer _hitSoundBuffer;
		sf::SoundBuffer _wingSoundBuffer;
		sf::SoundBuffer _pointSoundBuffer;

		std::unique_ptr<sf::Sound> _hitSound;
		std::unique_ptr<sf::Sound> _wingSound;
		std::unique_ptr<sf::Sound> _pointSound;
	};
}