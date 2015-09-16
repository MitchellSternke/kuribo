#include "InitialState.hpp"
#include "LevelState.hpp"

void InitialState::onUpdate()
{
	// Transfer control to the level state
	setState( new LevelState );
}
