#include "coin_object.h"

CoinObject::CoinObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color, Point3f location) :
	GameObject(_name, meshFilePath, _color) 
{
	init( location);
}

CoinObject::CoinObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId, Point3f location) :
  GameObject(_name, meshFilePath, textureImageFilename, texId) 
{ 
	init( location);
}

void CoinObject::init( Point3f location) 
{
	setScale( COIN_SCALE);
	rotation = rand() % 360;
	setTranslation( location);
}

void CoinObject::rotateCoin()
{
	rotation += COIN_ROTATION;
	if (0 > rotation)
	{
		rotation += 360;
	}
}

void CoinObject::update()
{
	rotateCoin();
}

void CoinObject::draw()
{
	glPushMatrix();

	glTranslatef( t.x, t.y, t.z);
	glScalef(s.x, s.y, s.z);
	glRotatef( rotation, ROTATION_AXIS.x, ROTATION_AXIS.y, ROTATION_AXIS.z);

	if (texture != NULL) { texture->bind(); }

	glColor3f(color.r, color.g, color.b);

	mesh.draw();

	if (texture != NULL) { texture->unBind(); }
	
	glPopMatrix();
}

float CoinObject::distanceFrom( GameObject* otherObject)
{
	return 0;
}

void CoinObject::collisionHandler(GameObject *gameObject, Collision collision) {
	return;
}

void CoinObject::generateCoins( Scene* scene)
{
	scene->gameObjects.push_back( new CoinObject("coin1", "objects/coin.obj", RGBColor(1.0, 1.0, 0.0), COIN_1_LOCATION));
	
	scene->gameObjects.push_back( new CoinObject("coin2", "objects/coin.obj", RGBColor(1.0, 1.0, 0.0), COIN_2_LOCATION));
	
	scene->gameObjects.push_back( new CoinObject("coin3", "objects/coin.obj", RGBColor(1.0, 1.0, 0.0), COIN_3_LOCATION));
	
	scene->gameObjects.push_back( new CoinObject("coin4", "objects/coin.obj", RGBColor(1.0, 1.0, 0.0), COIN_4_LOCATION));
	
	scene->gameObjects.push_back( new CoinObject("coin5", "objects/coin.obj", RGBColor(1.0, 1.0, 0.0), COIN_5_LOCATION));
	
	scene->gameObjects.push_back( new CoinObject("coin6", "objects/coin.obj", RGBColor(1.0, 1.0, 0.0), COIN_6_LOCATION));
	
	scene->gameObjects.push_back( new CoinObject("coin7", "objects/coin.obj", RGBColor(1.0, 1.0, 0.0), COIN_7_LOCATION));
	
	scene->gameObjects.push_back( new CoinObject("coin8", "objects/coin.obj", RGBColor(1.0, 1.0, 0.0), COIN_8_LOCATION));
	
	scene->gameObjects.push_back( new CoinObject("coin9", "objects/coin.obj", RGBColor(1.0, 1.0, 0.0), COIN_9_LOCATION));
	
	scene->gameObjects.push_back( new CoinObject("coin10", "objects/coin.obj", RGBColor(1.0, 1.0, 0.0), COIN_10_LOCATION));
	
	scene->gameObjects.push_back( new CoinObject("star", "objects/star.obj", RGBColor(1.0, 1.0, 0.0), STAR_LOCATION));
}
