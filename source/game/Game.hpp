#ifndef GAME_HPP
#define GAME_HPP

#include "GameStateManager.hpp"

class GraphicsSystem;
class InputSystem;

/**
 * Controls the flow of logic and manages various subsystems for the application.
 */
class Game
{
public:
	/**
	 * Initialize the game.
	 */
	Game( GraphicsSystem& graphicsSystem, InputSystem& inputSystem );

	/**
	 * Free all resources used by the game.
	 */
	~Game();

	/**
	 * Run the game.
	 */
	void run();

private:
	GameStateManager gameStateManager;
	GraphicsSystem& graphicsSystem;
	InputSystem& inputSystem;
};

#endif // GAME_HPP
