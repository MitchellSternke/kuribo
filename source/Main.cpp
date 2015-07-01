/**
 * @file
 * Contains the program entry point.
 */

#include <exception>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "game/Game.hpp"
#include "graphics/sdl2/Sdl2GraphicsSystem.hpp"
#include "input/sdl2/Sdl2InputSystem.hpp"

#define WINDOW_RESOLUTION_X 1024
#define WINDOW_RESOLUTION_Y 768

#define SCREEN_RESOLUTION_X 256
#define SCREEN_RESOLUTION_Y 224

static SDL_Window* window = NULL;

/**
 * Cleanup all resources used by libraries for program exit.
 */
static void cleanup()
{
	SDL_Quit();
}

/**
 * Initialize all libraries for use.
 */
static int initialize()
{
	// Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) != 0 )
	{
		std::cout << "Error: Failed to initialize SDL\nDetails:\n" << SDL_GetError() << std::endl;
		return -1;
	}

	// Create the window
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	window = SDL_CreateWindow(
		"kuribo",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		WINDOW_RESOLUTION_X,
		WINDOW_RESOLUTION_Y,
		SDL_WINDOW_OPENGL
	);
	if( window == NULL )
	{
		std::cout << "Error: Failed to create the SDL_Window\nDetails:\n" << SDL_GetError() << std::endl;
		return -1;
	}

	// Create the OpenGL context
	if( SDL_GL_CreateContext(window) == NULL )
	{
		std::cout << "Error: failed to create the OpenGL context\nDetails:\n" << SDL_GetError() << std::endl;
		return -1;
	}

	return 0;
}

/**
 * Program entry point.
 */
int main( int argc, char** argv )
{
	// Wrap everything in a try-catch
	try
	{
		if( initialize() != 0 )
		{
			std::cout << "initialize() failed\n";
			cleanup();
			return -1;
		}
		else
		{
			// Initialize subsystems
			Sdl2GraphicsSystem graphicsSystem( window, SCREEN_RESOLUTION_X, SCREEN_RESOLUTION_Y );
			Sdl2InputSystem inputSystem;

			// Run the game
			Game game(graphicsSystem, inputSystem);
			game.run();
		}
	}
	catch( std::exception& e )
	{
		std::cout << "Unhandled exception caught in main():\n" << e.what() << std::endl;
	}
	catch( ... )
	{
		std::cout << "Unknown exception caught in main()\n";
	}

	cleanup();

	return 0;
}
