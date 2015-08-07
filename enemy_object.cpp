#include "enemy_object.h"
#include "player_object.h"

extern PlayerObject* player;

EnemyObject::EnemyObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color, Point3f location) :
	GameObject(_name, meshFilePath, _color) 
{
	init( location);
	direction = Point3f( 0.0, 0.0, 0.0);
	speed = 0;
}

EnemyObject::EnemyObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId, Point3f location) :
  GameObject(_name, meshFilePath, textureImageFilename, texId) 
{ 
	init( location);
	direction = Point3f( 0.0, 0.0, 0.0);
	speed = 0;
}

void EnemyObject::init( Point3f location) 
{
	setScale( ENEMY_SCALE);
	setTranslation( location);
}

void EnemyObject::update()
{
	float distance = distanceFrom( player);
	Point3f playerLoc = player->getPosition();

	if ( ATTACK_DISTANCE > distance )
	{
		//put the enemy into attack mode!
		//dividing by distance approximately normalizes the result
		direction.x = (playerLoc.x - t.x) / distance;
		direction.y = (playerLoc.y - t.y) / distance;
		direction.z = (playerLoc.z - t.z) / distance;
		
		speed = ATTACK_SPEED;
		
		t.x = t.x + (speed * direction.x);
		t.z = t.z + (speed * direction.z);

		speed = 0; //if speed were set, reset it to 0
	}
	else
	{
		direction.x = 0.0;
		direction.y = 0.0;
		direction.z = 0.0;
	}

	return;
}

float EnemyObject::distanceFrom( GameObject* otherObject)
{
	float result = 0;
	
	Point3f otherLoc = otherObject->getPosition();
	float dx = t.x - otherLoc.x;
	float dy = t.y - otherLoc.y;
	float dz = t.z - otherLoc.z;
	
	result = sqrt( dx * dx + dz * dz); //just 2D distance
	
	//if it's too far in the y direction, we'll say they can't see each other or something
	if ( 1.0 < abs( dy) )
	{
		result = 1000.0;
	}
	
	return result;
}

void EnemyObject::collisionHandler(GameObject *gameObject, Collision collision) {
	return;
}

void EnemyObject::generateEnemies( Scene* scene)
{
	scene->gameObjects.push_back( new EnemyObject("enemy1", "objects/star.obj", RGBColor(1.0, 0.0, 0.0), ENEMY_1_LOCATION));
	
	scene->gameObjects.push_back( new EnemyObject("enemy2", "objects/star.obj", RGBColor(1.0, 0.0, 0.0), ENEMY_2_LOCATION));
}
