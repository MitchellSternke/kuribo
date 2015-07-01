#ifndef GRAPHICSSYSTEM_HPP
#define GRAPHICSSYSTEM_HPP

#include <cstdint>

/**
 * Interface for rendering images to the screen.
 */
class GraphicsSystem
{
public:
	virtual ~GraphicsSystem() {}

	/**
	 * Clear the screen.
	 */
	virtual void clearScreen()=0;

	/**
	 * Draw a rectangle.
	 *
	 * @param x the x coordinate.
	 * @param y the y coordinate.
	 * @param width the width of the rectangle, in pixels.
	 * @param height the height of the rectangle, in pixels.
	 */
	virtual void drawRectangle( int x, int y, int width, int height )=0;

	/**
	 * Get the height of the virtual screen, in pixels.
	 */
	virtual int getScreenHeight() const =0;

	/**
	 * Get the width of the virtual screen, in pixels.
	 */
	virtual int getScreenWidth() const =0;

	/**
	 * Set the color used for drawing primitives.
	 *
	 * @param r the red component.
	 * @param g the green component.
	 * @param b the blue component.
	 * @param a the alpha (transparency) component.
	 */
	virtual void setColor( uint8_t r, uint8_t g, uint8_t b )=0;

	/**
	 * Draw changes that have been made to the screen since the last update.
	 */
	virtual void updateScreen()=0;
};

#endif // GRAPHICSSYSTEM_HPP
