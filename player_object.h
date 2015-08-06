#ifndef __PLAYER_OBJECT_H__
#define __PLAYER_OBJECT_H__

#include "game_object.h"

#define GRAVITY -0.02
#define JUMP_VELOCITY 0.6
#define SPEED 0.2
#define LEFT_TURN .05
#define RIGHT_TURN -.05

class PlayerObject: public GameObject
{
	public:
	
		PlayerObject(const std::string& meshFilename, RGBColor color);
		PlayerObject(GLuint texId, const std::string& meshFilename, const std::string& textureImageFilename);
	
		void draw();
		void animate(); //moves the character 1 unit in the forward direction	
		void jump(); //jump the character
		void step( float direction);
		void turnLeft(); //turn character/camera to the left
		void turnRight(); //turn character/camera to the right
		
		Point3f getPosition();
		Point3f getDirection();
		
		float distanceFrom( GameObject* otherObject);
		void attack( GameObject* otherObject);
	
	
	private:
	
		Point3f rotAxisVector; //around which axis we spin the object
		float rotVelocity; //assuming it's centered at the origin. and rotation amount
		
		//note that current "location" is held by the translation vector in GameObject
		Point3f direction; //not velocity, because sometimes we want
		float directionAngle;
		float speed; //movement and sometimes not. easier to keep track.
		
		void turn( float degrees);
		

};

#endif //__ANIMATE_OBJECT_H__
