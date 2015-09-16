#ifndef INPUTSYSTEM_HPP
#define INPUTSYSTEM_HPP

/**
 * Buttons on an input controller.
 */
enum InputButton
{
	BUTTON_A,
	BUTTON_B,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_UP,
	BUTTON_START
};

constexpr int NUM_BUTTONS = 7; /**< The number of buttons defined for the input controller. */

/**
 * Interface for receiving input from the user.
 */
class InputSystem
{
public:
	virtual ~InputSystem() {}

	/**
	 * Determine if a given button is pressed.
	 */
	virtual bool buttonPressed( InputButton button ) const =0;

	/**
	 * Determine if a given button was pressed before the last frame update.
	 */
	virtual bool buttonPressedLastFrame( InputButton button ) const =0;

	/**
	 * Check if a shutdown signal was received from the user.
	 */
	virtual bool shutdownReceived() const =0;

	/**
	 * Update the state of all controllers.
	 */
	virtual void update()=0;
};

#endif // INPUTSYSTEM_HPP
