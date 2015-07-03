#include <cmath>
#include <set>

#include "Block.hpp"
#include "Layer.hpp"

Layer::Layer( int width, int height ) :
	xPosition(0.0f),
	yPosition(0.0f),
	width(width),
	height(height)
{
	blocks.resize(width * height, nullptr);
}

Layer::~Layer()
{
	// Find all blocks in the layer
	std::set<Block*> blockSet;
	for( auto block : blocks )
	{
		if( block != nullptr )
		{
			blockSet.insert(block);
		}
	}

	// And free them
	for( auto block : blockSet )
	{
		delete block;
	}
}

void Layer::addBlock( int x, int y, Block* block )
{
	if( block == nullptr )
	{
		return;
	}

	block->xPosition = x;
	block->yPosition = y;

	insertBlock( block );
}

Block* Layer::getBlock( int x, int y )
{
	// Check bounds
	if( x < 0 || x >= width || y < 0 || y >= height )
	{
		return nullptr;
	}

	return blocks[y * width + x];
}

const Block* Layer::getBlock( int x, int y ) const
{
	// Check bounds
	if( x < 0 || x >= width || y < 0 || y >= height )
	{
		return nullptr;
	}

	return blocks[y * width + x];
}

int Layer::getX() const
{
	return static_cast<int>(std::floor(xPosition));
}

int Layer::getY() const
{
	return static_cast<int>(std::floor(yPosition));
}

void Layer::insertBlock( Block* block )
{
	for( int y = 0; y < block->getHeight(); y++ )
	{
		for( int x = 0; x < block->getWidth(); x++ )
		{
			if( x < 0 || x >= width || y < 0 || y >= height )
			{
				continue;
			}

			blocks[y * width + x] = block;
		}
	}
}
