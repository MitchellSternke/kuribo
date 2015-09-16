#ifndef BLOCK_HPP
#define BLOCK_HPP

constexpr int BLOCK_SIZE = 16; /**< The size of a unit block, in pixels. */

/**
 * A tiled object that makes up the terrain of a level.
 */
class Block
{
	friend class Layer;
public:
	Block();
	virtual ~Block() {}

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
	int xPosition;
	int yPosition;
	int width;
	int height;
};

#endif // BLOCK_HPP
