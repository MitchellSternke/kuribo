#include "GameState.hpp"
#include "GameStateManager.hpp"

GameState::GameState() :
	stateManager(nullptr)
{
}

void GameState::popState()
{
	stateManager->popState();
}

void GameState::pushState( GameState* state )
{
	stateManager->pushState(state);
}

void GameState::setState( GameState* state )
{
	popState();
	pushState(state);
}
