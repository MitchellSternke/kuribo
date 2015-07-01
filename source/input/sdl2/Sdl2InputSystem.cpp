#include "Sdl2InputSystem.hpp"

Sdl2InputSystem::Sdl2InputSystem() :
	frameToggle(0),
	shutdown(false)
{
	for( int i = 0; i < 2; i++ )
	{
		for( int b = 0; b < NUM_BUTTONS; b++ )
		{
			buttonStates[i][b] = false;
		}
	}
}

bool Sdl2InputSystem::buttonPressed( InputButton button ) const
{
	return buttonStates[frameToggle][button];
}

bool Sdl2InputSystem::buttonPressedLastFrame( InputButton button ) const
{
	return buttonStates[frameToggle ^ 1][button];
}

bool Sdl2InputSystem::shutdownReceived() const
{
	return shutdown;
}

void Sdl2InputSystem::update()
{
	// Poll SDL events first
	SDL_Event event;
	while( SDL_PollEvent(&event) )
	{
		switch( event.type )
		{
			case SDL_KEYDOWN:
				switch( event.key.keysym.scancode )
				{
					case SDL_SCANCODE_ESCAPE:
						shutdown = true;
						break;

					default:
						break;
				}
				break;

			case SDL_QUIT:
				shutdown = true;
				break;

			default:
				break;
		}
	}

	// Check the keyboard for button states
	frameToggle ^= 1;
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	buttonStates[frameToggle][BUTTON_A]     = keystates[SDL_SCANCODE_X];
	buttonStates[frameToggle][BUTTON_B]     = keystates[SDL_SCANCODE_Z];
	buttonStates[frameToggle][BUTTON_DOWN]  = keystates[SDL_SCANCODE_DOWN];
	buttonStates[frameToggle][BUTTON_LEFT]  = keystates[SDL_SCANCODE_LEFT];
	buttonStates[frameToggle][BUTTON_RIGHT] = keystates[SDL_SCANCODE_RIGHT];
	buttonStates[frameToggle][BUTTON_UP]    = keystates[SDL_SCANCODE_UP];
	buttonStates[frameToggle][BUTTON_START] = keystates[SDL_SCANCODE_RETURN];
}
