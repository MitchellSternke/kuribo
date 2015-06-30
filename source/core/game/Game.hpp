#ifndef GAME_HPP
#define GAME_HPP

#include "GameStateManager.hpp"

/**
 * Controls the flow of logic and manages various subsystems for the application.
 */
class Game
{
public:
	/**
	 * Initialize the game.
	 */
	Game();

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
};

#endif // GAME_HPP
