#include "player_object.h"
#include "coin_object.h"

PlayerObject::PlayerObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color) :
	GameObject(_name, meshFilePath, _color) 
{
	init();
}

PlayerObject::PlayerObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId) :
  GameObject(_name, meshFilePath, textureImageFilename, texId) 
{ 
	init();
}

void PlayerObject::init() 
{
	lives = 3;
	coins = 0;
	t = INITIAL_TRANSLATION;
	directionAngle = INITIAL_DIRECTION;
	setScale(PLAYER_SCALE);
	turn(0);
}

void PlayerObject::updateHandler()
{
	t.x = t.x + (speed * direction.x);
	t.z = t.z + (speed * direction.z);

	speed = 0; //if speed were set, reset it to 0
	
	t.y = t.y + (SPEED * direction.y); //now time for up and down
	if (t.y < 0)
	{
		t.y = 0;
	}
	
	if (direction.y != 0) {
		direction.y += GRAVITY;
		if ( direction.y < MAX_Y_SPEED )
		{
			direction.y = MAX_Y_SPEED;
		}
	}

	return;
}

void PlayerObject::jump()
{
	direction.y = JUMP_VELOCITY;
	//t.y += JUMP_VELOCITY;
	return;
}

void PlayerObject::step( float direction)
{
	speed = direction * SPEED;
	return;
}

void PlayerObject::turnLeft()
{
	turn( LEFT_TURN);
	return;
}

void PlayerObject::turnRight()
{
	turn( RIGHT_TURN);
	return;
}

Point3f PlayerObject::getDirection()
{
	return direction;
}

float PlayerObject::distanceFrom( GameObject* otherObject)
{
	return 0;
}

void PlayerObject::attack( GameObject* otherObject)
{
	return;
}

void PlayerObject::turn( float degrees)
{
	//update the directionAngle
	directionAngle += degrees;
	if ( 360 < directionAngle )
	{
		directionAngle -= 360;
	}
	else if ( 0 > directionAngle )
	{
		directionAngle += 360;
	}
	
	//now update the direction vector
	direction.x = sin( directionAngle);
	direction.z = cos( directionAngle);

	//y is updated as a part of jump/animate.

	return;
}

void PlayerObject::die()
{
	lives--;
	setTranslation( INITIAL_TRANSLATION);
	directionAngle = INITIAL_DIRECTION;
	direction = Point3f( 0.0, 0.0, 0.0);
	return;
}

void PlayerObject::addCoin()
{
	coins++;
	
	if ( coins == TOTAL_COINS )
	{
		//win();
	}
	
	return;
}

void PlayerObject::collisionHandler(GameObject *gameObject, Collision collision) {
	if (collision.target.getBBox().max.y <= t.y) {
		direction.y = 0;
	}
}
