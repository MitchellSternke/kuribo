#include "LevelState.hpp"

LevelState::LevelState()
{
}

LevelState::~LevelState()
{
}

void LevelState::onRender( GraphicsSystem& graphics ) const
{
	level.render(graphics, 0, 256, 0, 224);
}

void LevelState::onUpdate()
{
	level.update();
}
