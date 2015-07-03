#include "Block.hpp"

Block::Block() :
	width(1),
	height(1)
{
}

int Block::getHeight() const
{
	return height;
}

int Block::getWidth() const
{
	return width;
}

int Block::getX() const
{
	return xPosition;
}

int Block::getY() const
{
	return yPosition;
}
