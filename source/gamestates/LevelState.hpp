#ifndef LEVELSTATE_HPP
#define LEVELSTATE_HPP

#include "../game/GameState.hpp"
#include "../level/Level.hpp"

/**
 * Handles the state where the player interacts with levels of the game.
 */
class LevelState : public GameState
{
public:
	LevelState();
	~LevelState();

private:
	Level level;

	void onRender( GraphicsSystem& graphics ) const;
	void onUpdate();
};

#endif // LEVELSTATE_HPP
