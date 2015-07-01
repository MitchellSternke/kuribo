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
		// Render
		graphicsSystem.clearScreen();
		gameStateManager.render(graphicsSystem);
		graphicsSystem.updateScreen();

		// Handle input
		inputSystem.update();

		// Do logic updates
		gameStateManager.update();
	}
}
