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
	addLayer(layer);
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
		}
		else
		{
			layer->xPosition += xVelocity;
		}
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
		}
		else
		{
			layer->xPosition += xVelocity;
		}
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
		}
		else
		{
			layer->yPosition += yVelocity;
		}
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
		}
		else
		{
			layer->yPosition += yVelocity;
		}
		yVelocity = 0.0f;
	}
}

void Level::updateSprites()
{
}
