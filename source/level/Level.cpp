#include <cmath>
#include <set>

#include "../graphics/GraphicsSystem.hpp"

#include "Block.hpp"
#include "Layer.hpp"
#include "Level.hpp"
#include "Sprite.hpp"

Level::Level()
{
	// Setup a test level
	Layer* layer = new Layer(256, 14);
	for( int x = 0; x < 256; x++ )
	{
		layer->addBlock(x, 13, new Block(BLOCK_SOLID));
	}
	layer->xVelocity = -0.25f;
	layer->yVelocity = -0.125f;
	addLayer(layer);

	layer = new Layer(256, 14);
	for( int y = 0; y < 14; y++ )
	{
		layer->addBlock(12, y, new Block(BLOCK_SOLID));
	}
	layer->xVelocity = -0.25f;
	addLayer(layer);

	Sprite* sprite = new Sprite();
	sprite->width = 16;
	sprite->height = 16;
	sprite->xVelocity = 1.0f;
	sprite->yVelocity = 0.5f;
	sprite->yAcceleration = 0.05f;
	addSprite(sprite);
}

Level::~Level()
{
	// Free all layers
	for( auto layer : layers )
	{
		delete layer;
	}

	// Free all sprites
	for( auto sprite : sprites )
	{
		delete sprite;
	}
}

void Level::addLayer( Layer* layer )
{
	layers.push_back(layer);
}

void Level::addSprite( Sprite* sprite )
{
	sprites.push_back(sprite);
}

bool Level::isSpriteStandingOnLayer( const Layer* layer, const Sprite* sprite ) const
{
	// Check the bottom pixels of the sprite's bounding box
	for( int x = 0; x < sprite->width; x++ )
	{
		if( layer->getCollisionTypeAtPixel(sprite->getLeft() + x, sprite->getBottom() + 1) & COLLISION_TOP )
		{
			return true;
		}
	}

	return false;
}

void Level::moveLayerDown( Layer* layer )
{
	// Move any sprites that are standing on this layer or colliding with the bottom edge of it
	for( auto sprite : sprites )
	{
		if( isSpriteStandingOnLayer(layer, sprite) )
		{
			moveSpriteDown(sprite);
			continue;
		}

		for( int x = 0; x < sprite->width; x++ )
		{
			if( layer->getCollisionTypeAtPixel(sprite->getLeft() + x, sprite->getTop() - 1) & COLLISION_BOTTOM )
			{
				moveSpriteDown(sprite);
				break;
			}
		}
	}

	layer->yPosition++;
}

void Level::moveLayerLeft( Layer* layer )
{
	// Move any sprites that are standing on this layer or colliding with the left edge of it
	for( auto sprite : sprites )
	{
		if( isSpriteStandingOnLayer(layer, sprite) )
		{
			moveSpriteLeft(sprite);
			continue;
		}

		for( int y = 0; y < sprite->height; y++ )
		{
			if( layer->getCollisionTypeAtPixel(sprite->getRight() + 1, sprite->getTop() + y) & COLLISION_LEFT )
			{
				moveSpriteLeft(sprite);
				break;
			}
		}
	}

	layer->xPosition--;
}

void Level::moveLayerRight( Layer* layer )
{
	// Move any sprites that are standing on this layer or colliding with the right edge of it
	for( auto sprite : sprites )
	{
		if( isSpriteStandingOnLayer(layer, sprite) )
		{
			moveSpriteRight(sprite);
			continue;
		}

		for( int y = 0; y < sprite->height; y++ )
		{
			if( layer->getCollisionTypeAtPixel(sprite->getLeft() - 1, sprite->getTop() + y) & COLLISION_RIGHT )
			{
				moveSpriteRight(sprite);
				break;
			}
		}
	}

	layer->xPosition++;
}

void Level::moveLayerUp( Layer* layer )
{
	// Move any sprites that are standing on this layer
	for( auto sprite : sprites )
	{
		if( isSpriteStandingOnLayer(layer, sprite) )
		{
			moveSpriteUp(sprite);
		}
	}

	layer->yPosition--;
}

bool Level::moveSpriteDown( Sprite* sprite )
{
	if( tryMoveSpriteDown(sprite) )
	{
		moveSpriteDown(sprite, 1.0f);
		return true;
	}
	return false;
}

void Level::moveSpriteDown( Sprite* sprite, float dy )
{
	sprite->yPosition += dy;
}

bool Level::moveSpriteLeft( Sprite* sprite )
{
	if( tryMoveSpriteLeft(sprite) )
	{
		moveSpriteLeft(sprite, -1.0f);
		return true;
	}
	return false;
}

void Level::moveSpriteLeft( Sprite* sprite, float dx )
{
	sprite->xPosition += dx;
}

bool Level::moveSpriteRight( Sprite* sprite )
{
	if( tryMoveSpriteRight(sprite) )
	{
		moveSpriteRight(sprite, 1.0f);
		return true;
	}
	return false;
}

void Level::moveSpriteRight( Sprite* sprite, float dx )
{
	sprite->xPosition += dx;
}

bool Level::moveSpriteUp( Sprite* sprite )
{
	if( tryMoveSpriteUp( sprite ) )
	{
		moveSpriteUp(sprite, -1.0f);
		return true;
	}
	return false;
}

void Level::moveSpriteUp( Sprite* sprite, float dy )
{
	sprite->yPosition += dy;
}

void Level::render( GraphicsSystem& graphics, int left, int right, int top, int bottom ) const
{
	// Render layers of blocks
	for( auto layer : layers )
	{
		std::set<Block*> blocks;
		for( int x = left; x < right + BLOCK_SIZE; x += BLOCK_SIZE )
		{
			for( int y = top; y < bottom + BLOCK_SIZE; y += BLOCK_SIZE )
			{
				auto block = layer->getBlockAtPixel(x, y);
				if( block != nullptr )
				{
					blocks.insert(block);
				}
			}
		}

		graphics.setColor(0, 0, 0xff);
		for( auto block : blocks )
		{
			graphics.drawRectangleBordered( block->getX() * BLOCK_SIZE - left + layer->xPosition, block->getY() * BLOCK_SIZE - top + layer->yPosition, BLOCK_SIZE, BLOCK_SIZE );
		}
	}

	// Render sprites
	graphics.setColor(0xff, 0, 0);
	for( auto sprite : sprites )
	{
		if( sprite->xPosition <= right || sprite->xPosition + sprite->width > left ||
			sprite->yPosition <= bottom || sprite->yPosition + sprite->height > top )
		{
			graphics.drawRectangleBordered( sprite->getX(), sprite->getY(), sprite->width, sprite->height );
		}
	}
}

bool Level::tryMoveSpriteDown( Sprite* sprite )
{
	// Check for blocks below
	for( auto layer : layers )
	{
		for( int x = 0; x < sprite->width; x++ )
		{
			if( layer->getCollisionTypeAtPixel(sprite->getLeft() + x, sprite->getBottom() + 1) & COLLISION_TOP )
			{
				return false;
			}
		}
	}

	return true;
}

bool Level::tryMoveSpriteLeft( Sprite* sprite )
{
	// Check for blocks to the left
	for( auto layer : layers )
	{
		for( int y = 0; y < sprite->height; y++ )
		{
			if( layer->getCollisionTypeAtPixel(sprite->getLeft() - 1, sprite->getTop() + y) & COLLISION_RIGHT )
			{
				return false;
			}
		}
	}

	return true;
}

bool Level::tryMoveSpriteRight( Sprite* sprite )
{
	// Check for blocks to the right
	for( auto layer : layers )
	{
		for( int y = 0; y < sprite->height; y++ )
		{
			if( layer->getCollisionTypeAtPixel(sprite->getRight() + 1, sprite->getTop() + y) & COLLISION_LEFT )
			{
				return false;
			}
		}
	}

	return true;
}

bool Level::tryMoveSpriteUp( Sprite* sprite )
{
	// Check for blocks above
	for( auto layer : layers )
	{
		for( int x = 0; x < sprite->width; x++ )
		{
			if( layer->getCollisionTypeAtPixel(sprite->getLeft() + x, sprite->getTop() - 1) & COLLISION_BOTTOM )
			{
				return false;
			}
		}
	}

	return true;
}

void Level::update()
{
	// Update all layers
	updateLayers();

	// Update all sprites
	updateSprites();
}

void Level::updateLayer(Layer* layer)
{
	// Handle motion
	updateLayerXMotion(layer);
	updateLayerYMotion(layer);

	// Handle update logic
	layer->onUpdate();
}

void Level::updateLayers()
{
	// Update each layer
	for( auto layer : layers )
	{
		updateLayer(layer);
	}
}

void Level::updateLayerXMotion( Layer* layer )
{
	// Move left/right one pixel at a time
	float xVelocity = layer->xVelocity;
	while( xVelocity >= 1.0f )
	{
		moveLayerRight(layer);
		xVelocity--;
	}
	if( xVelocity > 0.0f )
	{
		if( std::floor(layer->xPosition + xVelocity) == std::floor(layer->xPosition + 1) )
		{
			moveLayerRight(layer);
			layer->xPosition--;
		}
		layer->xPosition += xVelocity;
		xVelocity = 0.0f;
	}
	while( xVelocity <= -1.0f )
	{
		moveLayerLeft(layer);
		xVelocity++;
	}
	if( xVelocity < 0.0f )
	{
		if( std::floor(layer->xPosition + xVelocity) == std::floor(layer->xPosition - 1) )
		{
			moveLayerLeft(layer);
			layer->xPosition++;
		}
		layer->xPosition += xVelocity;
		xVelocity = 0.0f;
	}
}

void Level::updateLayerYMotion( Layer* layer )
{
	// Move up/down one pixel at a time
	float yVelocity = layer->yVelocity;
	while( yVelocity >= 1.0f )
	{
		moveLayerDown(layer);
		yVelocity--;
	}
	if( yVelocity > 0.0f )
	{
		if( std::floor(layer->yPosition + yVelocity) == std::floor(layer->yPosition + 1) )
		{
			moveLayerDown(layer);
			layer->yPosition--;
		}
		layer->yPosition += yVelocity;
		yVelocity = 0.0f;
	}
	while( yVelocity <= -1.0f )
	{
		moveLayerUp(layer);
		yVelocity++;
	}
	if( yVelocity < 0.0f )
	{
		if( std::floor(layer->yPosition + yVelocity) == std::floor(layer->yPosition - 1) )
		{
			moveLayerUp(layer);
			layer->yPosition++;
		}
		layer->yPosition += yVelocity;
		yVelocity = 0.0f;
	}
}

void Level::updateSprite( Sprite* sprite )
{
	// Handle motion
	updateSpriteXMotion(sprite);
	updateSpriteYMotion(sprite);

	// Handle update logic
	sprite->onUpdate();
}

void Level::updateSprites()
{
	// Update each sprite
	for( auto sprite : sprites )
	{
		updateSprite( sprite );
	}
}

void Level::updateSpriteXMotion( Sprite* sprite )
{
	sprite->xVelocity += sprite->xAcceleration;

	// Move left/right one pixel at a time
	float xVelocity = sprite->xVelocity;
	while( xVelocity >= 1.0f )
	{
		if( moveSpriteRight(sprite) )
		{
			xVelocity--;
		}
		else
		{
			sprite->xVelocity = 0.0f;
			return;
		}
	}
	if( xVelocity > 0.0f )
	{
		if( std::floor(sprite->xPosition + xVelocity) == std::floor(sprite->xPosition + 1) )
		{
			if( tryMoveSpriteRight(sprite) )
			{
				moveSpriteRight(sprite, xVelocity);
			}
			else
			{
				sprite->xVelocity = 0.0f;
				return;
			}
		}
		else
		{
			sprite->xPosition += xVelocity;
		}
		xVelocity = 0.0f;
	}
	while( xVelocity <= -1.0f )
	{
		if( moveSpriteLeft(sprite) )
		{
			xVelocity++;
		}
		else
		{
			sprite->xVelocity = 0.0f;
			return;
		}
	}
	if( xVelocity < 0.0f )
	{
		if( std::floor(sprite->xPosition + xVelocity) == std::floor(sprite->xPosition - 1) )
		{
			if( tryMoveSpriteLeft(sprite) )
			{
				moveSpriteLeft(sprite, xVelocity);
			}
			else
			{
				sprite->xVelocity = 0.0f;
				return;
			}
		}
		sprite->xPosition += xVelocity;
		xVelocity = 0.0f;
	}
}

void Level::updateSpriteYMotion( Sprite* sprite )
{
	sprite->yVelocity += sprite->yAcceleration;

	// Move up/down one pixel at a time
	float yVelocity = sprite->yVelocity;
	while( yVelocity >= 1.0f )
	{
		if( moveSpriteDown(sprite) )
		{
			yVelocity--;
		}
		else
		{
			sprite->yVelocity = 0.0f;
			return;
		}
	}
	if( yVelocity > 0.0f )
	{
		if( std::floor(sprite->yPosition + yVelocity) == std::floor(sprite->yPosition + 1) )
		{
			if( tryMoveSpriteDown(sprite) )
			{
				moveSpriteDown(sprite, yVelocity);
			}
			else
			{
				sprite->yVelocity = 0.0f;
				return;
			}
		}
		else
		{
			sprite->yPosition += yVelocity;
		}
		yVelocity = 0.0f;
	}
	while( yVelocity <= -1.0f )
	{
		if( moveSpriteUp(sprite) )
		{
			yVelocity++;
		}
		else
		{
			sprite->yVelocity = 0.0f;
			return;
		}
	}
	if( yVelocity < 0.0f )
	{
		if( std::floor(sprite->yPosition + yVelocity) == std::floor(sprite->yPosition - 1) )
		{
			if( tryMoveSpriteUp(sprite) )
			{
				moveSpriteUp(sprite, yVelocity);
			}
			else
			{
				sprite->yVelocity = 0.0f;
				return;
			}
		}
		sprite->yPosition += yVelocity;
		yVelocity = 0.0f;
	}
}
