#ifndef GAMESTATEMANAGER_HPP
#define GAMESTATEMANAGER_HPP

#include <list>
#include <set>

class GameState;

/**
 * Manages the execution of different game states.
 */
class GameStateManager
{
public:
	~GameStateManager();

	/**
	 * Check if a game state is currently running.
	 */
	bool isRunning() const;

	/**
	 * Pop the current game state off of the stack.
	 */
	void popState();

	/**
	 * Push a game state onto the stack and begin executing it.
	 */
	void pushState( GameState* state );

	/**
	 * Render the current state.
	 */
	void render() const;

	/**
	 * Update the current state by one frame.
	 */
	void update();

private:
	std::set<GameState*> deadStates;
	std::list<GameState*> stateStack;
};

#endif // GAMESTATEMANAGER_HPP
