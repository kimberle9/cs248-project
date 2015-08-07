#include "coin_object.h"
#include "player_object.h"

extern PlayerObject* player;

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
	setTranslation(location);
	setRotation(rand() % 360, ROTATION_AXIS);
}

void CoinObject::rotateCoin()
{
	rotate(COIN_ROTATION);
	if (0 > rotation)
	{
		rotate(360);
	}
}

void CoinObject::updateHandler()
{
	rotateCoin();
	
	float distance = distanceFrom( player);

	if ( COLLECT_DISTANCE > distance )
	{
		//got the coin!
		player->addCoin();
		_destroyed = true;
	}
	
	return;
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
