#ifndef INITIALSTATE_HPP
#define INITIALSTATE_HPP

#include "../game/GameState.hpp"

/**
 * The initial game state executed when the program starts.
 */
class InitialState : public GameState
{
private:
	void onRender( GraphicsSystem& graphics ) const {}
	void onUpdate();
};

#endif // INITIALSTATE_HPP
