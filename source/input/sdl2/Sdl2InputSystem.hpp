#ifndef SDL2INPUTSYSTEM_HPP
#define SDL2INPUTSYSTEM_HPP

#include <SDL2/SDL.h>

#include "../InputSystem.hpp"

class Sdl2InputSystem : public InputSystem
{
public:
	Sdl2InputSystem();

	bool buttonPressed( InputButton button ) const;
	bool buttonPressedLastFrame( InputButton button ) const;
	bool shutdownReceived() const;
	void update();

private:
	bool buttonStates[2][NUM_BUTTONS];
	int frameToggle;
	bool shutdown;
};

#endif // SDL2INPUTSYSTEM_HPP
