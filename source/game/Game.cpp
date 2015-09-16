#include "Game.hpp"

#include "../gamestates/InitialState.hpp"
#include "../graphics/GraphicsSystem.hpp"
#include "../input/InputSystem.hpp"

Game::Game( GraphicsSystem& graphicsSystem, InputSystem& inputSystem ) :
	graphicsSystem(graphicsSystem),
	inputSystem(inputSystem)
{
	// Set the initial state of the game
	gameStateManager.pushState(new InitialState);
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
