#ifndef SDL2GRAPHICSSYSTEM_HPP
#define SDL2GRAPHICSSYSTEM_HPP

#include <SDL2/SDL.h>

#include "../GraphicsSystem.hpp"

/**
 * An SDL2/OpenGL graphics system.
 */
class Sdl2GraphicsSystem : public GraphicsSystem
{
public:
	/**
	 * Create a new SDL2/OpenGL graphics subsystem.
	 *
	 * @param window the SDL_Window to draw to.
	 * @param virtualScreenWidth the width of the virtual screen, in pixels.
	 * @param virtualScreenHeight the height of the virtual screen, in pixels.
	 */
	Sdl2GraphicsSystem( SDL_Window* window, int virtualScreenWidth, int virtualScreenHeight );

	void clearScreen();
	void drawRectangle( int x, int y, int width, int height );
	int getScreenHeight() const;
	int getScreenWidth() const;
	void setColor( uint8_t r, uint8_t g, uint8_t b );
	void updateScreen();

private:
	SDL_Window* window;
	int screenWidth;
	int screenHeight;
};

#endif // SDL2GRAPHICSSYSTEM_HPP
