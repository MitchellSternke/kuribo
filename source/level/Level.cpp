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
		layer->addBlock(x, 13, new Block());
	}
	layer->yVelocity = -0.125f;
	addLayer(layer);

	Sprite* sprite = new Sprite();
	sprite->width = 16;
	sprite->height = 16;
	sprite->xVelocity = 0.125f;
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

void Level::moveLayerDown( Layer* layer )
{
	layer->yPosition++;
}

void Level::moveLayerLeft( Layer* layer )
{
	layer->xPosition--;
}

void Level::moveLayerRight( Layer* layer )
{
	layer->xPosition++;
}

void Level::moveLayerUp( Layer* layer )
{
	layer->yPosition--;
}

void Level::moveSpriteDown( Sprite* sprite )
{
	if( tryMoveSpriteDown(sprite) )
	{
		sprite->yPosition++;
	}
}

void Level::moveSpriteLeft( Sprite* sprite )
{
	if( tryMoveSpriteLeft(sprite) )
	{
		sprite->xPosition--;
	}
}

void Level::moveSpriteRight( Sprite* sprite )
{
	if( tryMoveSpriteRight(sprite) )
	{
		sprite->xPosition++;
	}
}

void Level::moveSpriteUp( Sprite* sprite )
{
	if( tryMoveSpriteUp( sprite ) )
	{
		sprite->yPosition--;
	}
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
			graphics.drawRectangle( block->getX() * BLOCK_SIZE - left + layer->xPosition, block->getY() * BLOCK_SIZE - top + layer->yPosition, BLOCK_SIZE, BLOCK_SIZE );
		}
	}

	// Render sprites
	graphics.setColor(0xff, 0, 0);
	for( auto sprite : sprites )
	{
		if( sprite->xPosition <= right || sprite->xPosition + sprite->width > left ||
			sprite->yPosition <= bottom || sprite->yPosition + sprite->height > top )
		{
			graphics.drawRectangle( sprite->getX(), sprite->getY(), sprite->width, sprite->height );
		}
	}
}

bool Level::tryMoveSpriteDown( Sprite* sprite )
{
	// TODO: implement
	return true;
}

bool Level::tryMoveSpriteLeft( Sprite* sprite )
{
	// TODO: implement
	return true;
}

bool Level::tryMoveSpriteRight( Sprite* sprite )
{
	// TODO: implement
	return true;
}

bool Level::tryMoveSpriteUp( Sprite* sprite )
{
	// TODO: implement
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
	// Move left/right one pixel at a time
	float xVelocity = sprite->xVelocity;
	while( xVelocity >= 1.0f )
	{
		moveSpriteRight(sprite);
		xVelocity--;
	}
	if( xVelocity > 0.0f )
	{
		if( std::floor(sprite->xPosition + xVelocity) == std::floor(sprite->xPosition + 1) )
		{
			if( tryMoveSpriteRight(sprite) )
			{
				sprite->xPosition += xVelocity;
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
		moveSpriteLeft(sprite);
		xVelocity++;
	}
	if( xVelocity < 0.0f )
	{
		if( std::floor(sprite->xPosition + xVelocity) == std::floor(sprite->xPosition - 1) )
		{
			if( tryMoveSpriteLeft(sprite) )
			{
				sprite->xPosition += xVelocity;
			}
		}
		sprite->xPosition += xVelocity;
		xVelocity = 0.0f;
	}
}

void Level::updateSpriteYMotion( Sprite* sprite )
{
	// Move up/down one pixel at a time
	float yVelocity = sprite->yVelocity;
	while( yVelocity >= 1.0f )
	{
		moveSpriteDown(sprite);
		yVelocity--;
	}
	if( yVelocity > 0.0f )
	{
		if( std::floor(sprite->yPosition + yVelocity) == std::floor(sprite->yPosition + 1) )
		{
			if( tryMoveSpriteDown(sprite) )
			{
				sprite->yPosition += yVelocity;
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
		moveSpriteUp(sprite);
		yVelocity++;
	}
	if( yVelocity < 0.0f )
	{
		if( std::floor(sprite->yPosition + yVelocity) == std::floor(sprite->yPosition - 1) )
		{
			if( tryMoveSpriteUp(sprite) )
			{
				sprite->yPosition += yVelocity;
			}
		}
		sprite->yPosition += yVelocity;
		yVelocity = 0.0f;
	}
}
