#ifndef __PLAYER_OBJECT_H__
#define __PLAYER_OBJECT_H__

#include "game_object.h"

#define GRAVITY -0.17
#define JUMP_VELOCITY .9
#define SPEED 0.95
#define LEFT_TURN .23
#define RIGHT_TURN -.23
#define MAX_Y_SPEED -0.2

#define INITIAL_TRANSLATION Point3f(7.0, 1.2, 8.0)
#define INITIAL_DIRECTION 91

#define PLAYER_SCALE Point3f(.1, .1, .1)

class PlayerObject: public GameObject
{
	public:
	
		int lives;
		int coins;
	
		PlayerObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color);
		PlayerObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId);

		void init();
		void resetPlayer();

		void jump(); //jump the character
		void step( float direction);
		void turnLeft(); //turn character/camera to the left
		void turnRight(); //turn character/camera to the right
		
		Point3f getDirection();
		
		float distanceFrom( GameObject* otherObject);
		void attack( GameObject* otherObject);
		
		void die();
		void addCoin();
	
		void updateXHandler(); 
		void updateYHandler(); 
		void updateZHandler(); 
		void postUpdateHandler();

		void collisionHandler(GameObject *gameObject, Collision collision);

	private:
	
		Point3f rotAxisVector; //around which axis we spin the object
		float rotVelocity; //assuming it's centered at the origin. and rotation amount
		
		//note that current "location" is held by the translation vector in GameObject
		Point3f direction; //not velocity, because sometimes we want
		float directionAngle;
		float speed; //movement and sometimes not. easier to keep track.
		
		void turn( float degrees);
		

};

#endif //__PLAYER_OBJECT_H__
