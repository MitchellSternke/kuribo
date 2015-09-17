#include <cmath>

#include "Block.hpp"

Block::Block( BlockCollisionType collisionType ) :
	collisionType(collisionType),
	width(1),
	height(1)
{
}

int Block::getCollisionTypeAtPixel( int x, int y ) const
{
	switch( collisionType )
	{
		case BLOCK_NONE:
			return COLLISION_NONE;

		case BLOCK_PLATFORM:
			if( y == 0 )
			{
				return COLLISION_TOP;
			}
			else
			{
				return COLLISION_NONE;
			}

		case BLOCK_SLOPE_LEFT:
		{
			int h = static_cast<int>(std::floor(-1.0f * (static_cast<float>(height) / static_cast<float>(width)) * (x + 0.5f) + (height * BLOCK_SIZE)));
			if( y == h )
			{
				return COLLISION_TOP;
			}
			else
			{
				return COLLISION_NONE;
			}
		}

		case BLOCK_SLOPE_RIGHT:
		{
			int h = static_cast<int>(std::floor((static_cast<float>(height) / static_cast<float>(width)) * (x + 0.5f)));
			if( y == h )
			{
				return COLLISION_TOP;
			}
			else
			{
				return COLLISION_NONE;
			}
		}

		case BLOCK_SOLID:
			return COLLISION_BOTTOM | COLLISION_LEFT | COLLISION_RIGHT | COLLISION_TOP;

		default:
			return 0;
	}
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
