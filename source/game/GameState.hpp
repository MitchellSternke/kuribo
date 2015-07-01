#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

class GameStateManager;
class GraphicsSystem;

/**
 * A state of execution in the game.
 */
class GameState
{
	friend class GameStateManager;
public:
	GameState();
	virtual ~GameState() {}

protected:
	/**
	 * Called whenever this state is requested to render itself to the screen.
	 */
	virtual void onRender( GraphicsSystem& graphicsSystem ) const =0;

	/**
	 * Called once per frame to have the state update itself and perform any logic.
	 */
	virtual void onUpdate()=0;

	/**
	 * Pop the current state off of the state stack.
	 */
	void popState();

	/**
	 * Push a new state onto the top of the state stack.
	 */
	void pushState( GameState* state );

	/**
	 * Replace the current state with a different game state.
	 */
	void setState( GameState* state );

private:
	GameStateManager* stateManager;
};

#endif // GAMESTATE_HPP
