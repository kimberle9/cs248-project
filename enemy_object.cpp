#include "enemy_object.h"

EnemyObject::EnemyObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color, Point3f location) :
	GameObject(_name, meshFilePath, _color) 
{
	init( location);
}

EnemyObject::EnemyObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId, Point3f location) :
  GameObject(_name, meshFilePath, textureImageFilename, texId) 
{ 
	init( location);
}

void EnemyObject::init( Point3f location) 
{
	setScale( ENEMY_SCALE);
	setTranslation( location);
}

void EnemyObject::update()
{
	return;
}

float EnemyObject::distanceFrom( GameObject* otherObject)
{
	return 0;
}

void EnemyObject::collisionHandler(GameObject *gameObject, Collision collision) {
	return;
}

void EnemyObject::generateEnemies( Scene* scene)
{
	scene->gameObjects.push_back( new EnemyObject("coin", "objects/star.obj", RGBColor(1.0, 0.0, 0.0), ENEMY_1_LOCATION));
}
