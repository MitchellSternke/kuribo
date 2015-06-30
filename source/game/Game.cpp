#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
}

void Game::run()
{
	while( gameStateManager.isRunning() )
	{
		gameStateManager.render();
		gameStateManager.update();
	}
}
