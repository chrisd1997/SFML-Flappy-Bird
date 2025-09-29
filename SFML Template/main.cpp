#include <iostream>
#include "Game.hpp"
#include "DEFINITIONS.hpp"

int main()
{
	PixelPanic::Game(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird");

	return EXIT_SUCCESS;
}