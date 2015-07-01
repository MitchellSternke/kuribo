#include "Game.hpp"

#include "../graphics/GraphicsSystem.hpp"
#include "../input/InputSystem.hpp"

Game::Game( GraphicsSystem& graphicsSystem, InputSystem& inputSystem ) :
	graphicsSystem(graphicsSystem),
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
		graphicsSystem.clearScreen();
		gameStateManager.render();
		graphicsSystem.updateScreen();

		inputSystem.update();

		gameStateManager.update();
	}
}
