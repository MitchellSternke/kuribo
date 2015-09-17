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

	bool isSpriteStandingOnLayer( const Layer* layer, const Sprite* sprite ) const;
	void moveLayerDown( Layer* layer );
	void moveLayerLeft( Layer* layer );
	void moveLayerRight( Layer* layer );
	void moveLayerUp( Layer* layer );
	bool moveSpriteDown( Sprite* sprite );
	void moveSpriteDown( Sprite* sprite, float dy );
	bool moveSpriteLeft( Sprite* sprite );
	void moveSpriteLeft( Sprite* sprite, float dx );
	bool moveSpriteRight( Sprite* sprite );
	void moveSpriteRight( Sprite* sprite, float dx );
	bool moveSpriteUp( Sprite* sprite );
	void moveSpriteUp( Sprite* sprite, float dy );
	bool tryMoveSpriteDown( Sprite* sprite );
	bool tryMoveSpriteLeft( Sprite* sprite );
	bool tryMoveSpriteRight( Sprite* sprite );
	bool tryMoveSpriteUp( Sprite* sprite );
	void updateLayer(Layer* layer);
	void updateLayers();
	void updateLayerXMotion( Layer* layer );
	void updateLayerYMotion( Layer* layer );
	void updateSprite( Sprite* sprite );
	void updateSprites();
	void updateSpriteXMotion( Sprite* sprite );
	void updateSpriteYMotion( Sprite* sprite );
};

#endif // LEVEL_HPP
