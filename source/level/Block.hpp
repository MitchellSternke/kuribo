#ifndef BLOCK_HPP
#define BLOCK_HPP

constexpr int BLOCK_SIZE = 16; /**< The size of a unit block, in pixels. */

/**
 * Collision mask templates for entire blocks.
 */
enum BlockCollisionType
{
	BLOCK_NONE,        /**< Block does not cause collisions. */
	BLOCK_PLATFORM,    /**< Block only causes collisions from the top row of pixels from above. */
	BLOCK_SLOPE_LEFT,  /**< Block is slope shaped, increasing in height to the left, and behaves like a platform. */
	BLOCK_SLOPE_RIGHT, /**< Block is slope shaped, increasing in height to the right, and behaves like a platform. */
	BLOCK_SOLID        /**< Block causes collisions on all sides. */
};

/**
 * Collision masks for individual pixels of a block.
 */
enum PixelCollisionType
{
	COLLISION_NONE   = 0,        /**< Pixel does not cause collisions. */
	COLLISION_BOTTOM = (1 << 0), /**< Pixel causes collisions when hit below. */
	COLLISION_LEFT   = (1 << 1), /**< Pixel causes collisions when hit to the left. */
	COLLISION_RIGHT  = (1 << 2), /**< Pixel causes collisions when hit to the right. */
	COLLISION_TOP    = (1 << 3), /**< Pixel causes collisions when hit from above. */
};

/**
 * A tiled object that makes up the terrain of a level.
 */
class Block
{
	friend class Layer;
public:
	Block( BlockCollisionType collisionType );
	virtual ~Block() {}

	/**
	 * Get the collision type mask at a given pixel in a block.
	 */
	int getCollisionTypeAtPixel( int x, int y ) const;

	/**
	 * Get the height of the block, in tiles.
	 */
	int getHeight() const;

	/**
	 * Get the width of the block, in tiles.
	 */
	int getWidth() const;

	/**
	 * Get the x position of the block on its layer, in tiles.
	 */
	int getX() const;

	/**
	 * Get the y position of the block on its layer, in tiles.
	 */
	int getY() const;

private:
	BlockCollisionType collisionType;
	int xPosition;
	int yPosition;
	int width;
	int height;
};

#endif // BLOCK_HPP
