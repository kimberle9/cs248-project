#include "player_object.h"

PlayerObject::PlayerObject(const std::string& meshFilename, RGBColor _color) :
	GameObject( meshFilename, _color) 
{
}

PlayerObject::PlayerObject(GLuint texId, const std::string& meshFilename, const std::string& textureImageFilename) : GameObject( texId, meshFilename, textureImageFilename) 
{ 
}

void PlayerObject::draw()
{
	glPushMatrix();

	glColor3f(color.r, color.g, color.b);

    glTranslatef(t.x, t.y, t.z);
    glScalef( 0.1, 0.1, 0.1);

	if (texture != NULL) { texture->bind(); }
	mesh.draw();
	if (texture != NULL) { texture->unBind(); }

	glPopMatrix();
}

void PlayerObject::animate()
{
	t.x = t.x + (speed * direction.x);
	t.z = t.z + (speed * direction.z);

	speed = 0; //if speed were set, reset it to 0
	
	t.y = t.y + (SPEED * direction.y); //now time for up and down
	float ground = 0;
	if ( t.y < ground )
	{
		t.y = ground;
		direction.y = 0;
	}
	else
	{
		direction.y += GRAVITY;
	}

	return;
}

void PlayerObject::jump()
{
	direction.y = JUMP_VELOCITY;
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

Point3f PlayerObject::getPosition()
{
	return t;
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
