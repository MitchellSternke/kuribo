#ifndef SPRITE_HPP
#define SPRITE_HPP

/**
 * A moving object in a level.
 */
class Sprite
{
	friend class Level;
public:
	Sprite();
	virtual ~Sprite() {}

protected:
	/**
	 * Called every frame for the sprite to do any update logic.
	 */
	virtual void onUpdate() {}

private:
	float xPosition;
	float yPosition;
	float xVelocity;
	float yVelocity;
	float xAcceleration;
	float yAcceleration;
};

#endif // SPRITE_HPP
