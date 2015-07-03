#ifndef LAYER_HPP
#define LAYER_HPP

#include <vector>

class Block;

/**
 * A grid of blocks in a level.
 */
class Layer
{
	friend class Level;
public:
	/**
	 * Create a new layer.
	 *
	 * @param width the width of the layer, in tiles.
	 * @param height the height of the layer, in tiles.
	 */
	Layer( int width, int height );

	/**
	 * Destroy a layer and all blocks contained in it.
	 */
	virtual ~Layer();

	/**
	 * Add a block to the layer.
	 */
	void addBlock( int x, int y, Block* block );

	/**
	 * Get the block located at a position on the layer.
	 */
	Block* getBlock( int x, int y );

	/**
	 * Get the block located at a position on the layer.
	 */
	const Block* getBlock( int x, int y ) const;

	/**
	 * Get the layer's x position, in pixels.
	 */
	int getX() const;

	/**
	 * Get the layer's y position, in pixels.
	 */
	int getY() const;

private:
	float xPosition;
	float yPosition;
	int width;
	int height;
	std::vector<Block*> blocks;

	void insertBlock( Block* block );
};

#endif // LAYER_HPP
