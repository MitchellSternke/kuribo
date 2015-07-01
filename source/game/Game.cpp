#include "Game.hpp"

#include "../input/InputSystem.hpp"

Game::Game( InputSystem& inputSystem ) :
	inputSystem(inputSystem)
{
}

Game::~Game()
{
}

void Game::run()
{
	while( !inputSystem.shutdownReceived() && gameStateManager.isRunning() )
	{
		gameStateManager.render();

		inputSystem.update();

		gameStateManager.update();
	}
}
