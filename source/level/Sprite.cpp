#include <cmath>

#include "Sprite.hpp"

Sprite::Sprite() :
	xPosition(0.0f),
	yPosition(0.0f),
	xVelocity(0.0f),
	yVelocity(0.0f),
	xAcceleration(0.0f),
	yAcceleration(0.0f)
{
}

int Sprite::getX() const
{
	return static_cast<int>(std::floor(xPosition));
}

int Sprite::getY() const
{
	return static_cast<int>(std::floor(yPosition));
}
