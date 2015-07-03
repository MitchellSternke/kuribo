#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <list>

class Block;
class GraphicsSystem;
class Layer;
class Sprite;

/**
 * Stores and handles interactions between all Sprites, Blocks, and Layers.
 */
class Level
{
public:
	Level();
	~Level();

	/**
	 * Add a layer to the Level. It will be added as the lowest priority layer.
	 */
	void addLayer( Layer* layer );

	/**
	 * Add a sprite to the Level.
	 */
	void addSprite( Sprite* sprite );

	/**
	 * Render a portion of the level.
	 *
	 * @param graphics the GraphicsSystem to draw to.
	 * @param left the left coordinate for the rendering rectangle, in pixels.
	 * @param right the right coordinate for the rendering rectangle, in pixels.
	 * @param top the top coordinate for the rendering rectangle, in pixels.
	 * @param bottom the bottom coordinate for the rendering rectangle, in pixels.
	 */
	void render( GraphicsSystem& graphics, int left, int right, int top, int bottom ) const;

	/**
	 * Update the level by one frame.
	 */
	void update();

private:
	std::list<Layer*> layers;
	std::list<Sprite*> sprites;
};

#endif // LEVEL_HPP
