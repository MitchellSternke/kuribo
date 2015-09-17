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

	/**
	 * Get the bottom y coordinate of the sprite's bounding box.
	 */
	int getBottom() const;

	/**
	 * Get the left x coordinate of the sprite's bounding box.
	 */
	int getLeft() const;

	/**
	 * Get the right x coordinate of the sprite's bounding box.
	 */
	int getRight() const;

	/**
	 * Get the top y coordinate of the sprite's bounding box.
	 */
	int getTop() const;

	/**
	 * Get the x position of the sprite, in pixels.
	 */
	int getX() const;

	/**
	 * Get the y position of the sprite, in pixels.
	 */
	int getY() const;

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
	int width;
	int height;
};

#endif // SPRITE_HPP
