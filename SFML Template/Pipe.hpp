#pragma once

#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include <vector>
#include "DEFINITIONS.hpp"

namespace PixelPanic
{
	class Pipe
	{
	public:
		Pipe(GameDataRef data);

		void SpawnBottomPipe();
		void SpawnTopPipe();
		void SpawnInvisiblePipe();
		void MovePipes(float dt);
		void DrawPipes();
		void RandomizePipeOffset();

	private:
		GameDataRef _data;
		std::vector<sf::Sprite> pipeSprites;

		int _landHeight;
		int _pipeSpawnYOffset;
	};
}