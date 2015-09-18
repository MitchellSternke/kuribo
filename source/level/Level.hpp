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

	/**
	 * Check if a sprite is standing on top of any block in a given layer.
	 */
	bool isSpriteStandingOnLayer( const Layer* layer, const Sprite* sprite ) const;

	/**
	 * Move a layer down by one pixel.
	 */
	void moveLayerDown( Layer* layer );

	/**
	 * Move a layer to the left by one pixel.
	 */
	void moveLayerLeft( Layer* layer );

	/**
	 * Move a layer to the right by one pixel.
	 */
	void moveLayerRight( Layer* layer );

	/**
	 * Move a layer up by one pixel.
	 */
	void moveLayerUp( Layer* layer );

	/**
	 * Move a sprite down by one pixel.
	 */
	bool moveSpriteDown( Sprite* sprite );

	/**
	 * Move a sprite down by a given amount.
	 */
	void moveSpriteDown( Sprite* sprite, float dy );

	/**
	 * Move a sprite to the left by one pixel.
	 */
	bool moveSpriteLeft( Sprite* sprite );

	/**
	 * Move a sprite to the left by a given amount.
	 */
	void moveSpriteLeft( Sprite* sprite, float dx );

	/**
	 * Move a sprite to the right by one pixel.
	 */
	bool moveSpriteRight( Sprite* sprite );

	/**
	 * Move a sprite to the right by a given amount.
	 */
	void moveSpriteRight( Sprite* sprite, float dx );

	/**
	 * Move a sprite up by one pixel.
	 */
	bool moveSpriteUp( Sprite* sprite );

	/**
	 * Move a sprite up by a given amount.
	 */
	void moveSpriteUp( Sprite* sprite, float dy );

	/**
	 * See if it is possible to move a sprite down by one pixel.
	 */
	bool tryMoveSpriteDown( Sprite* sprite );

	/**
	 * See if it is possible to move a sprite to the left by one pixel.
	 */
	bool tryMoveSpriteLeft( Sprite* sprite );

	/**
	 * See if it is possible to move a sprite to the right by one pixel.
	 */
	bool tryMoveSpriteRight( Sprite* sprite );

	/**
	 * See if it is possible to move a sprite up by one pixel.
	 */
	bool tryMoveSpriteUp( Sprite* sprite );

	/**
	 * Update a layer by one frame.
	 */
	void updateLayer(Layer* layer);

	/**
	 * Update all layers by one frame.
	 */
	void updateLayers();

	/**
	 * Update layer motion in the x direction.
	 */
	void updateLayerXMotion( Layer* layer );

	/**
	 * Update layer motion in the y direction.
	 */
	void updateLayerYMotion( Layer* layer );

	/**
	 * Update a sprite by one frame.
	 */
	void updateSprite( Sprite* sprite );

	/**
	 * Update all sprites by one frame.
	 */
	void updateSprites();

	/**
	 * Update sprite motion in the x direction.
	 */
	void updateSpriteXMotion( Sprite* sprite );

	/**
	 * Update sprite motion in the y direction.
	 */
	void updateSpriteYMotion( Sprite* sprite );
};

#endif // LEVEL_HPP
