#include "GameState.hpp"
#include "GameStateManager.hpp"

GameStateManager::~GameStateManager()
{
	// Free all game states
	for( auto state : stateStack )
	{
		delete state;
	}
}

bool GameStateManager::isRunning() const
{
	return !stateStack.empty();
}

void GameStateManager::popState()
{
	if( !stateStack.empty() )
	{
		GameState* state = stateStack.back();
		deadStates.insert(state);
		stateStack.pop_back();
	}
}

void GameStateManager::pushState( GameState* state )
{
	state->stateManager = this;
	stateStack.push_back(state);
}

void GameStateManager::render( GraphicsSystem& graphicsSystem ) const
{
	if( !stateStack.empty() )
	{
		GameState* state = stateStack.back();
		state->onRender(graphicsSystem);
	}
}

void GameStateManager::update()
{
	if( !stateStack.empty() )
	{
		GameState* state = stateStack.front();
		state->onUpdate();
	}

	// Remove any dead states
	for( auto state : deadStates )
	{
		delete state;
	}
	deadStates.clear();
}
