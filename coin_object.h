#ifndef __COIN_OBJECT_H__
#define __COIN_OBJECT_H__

#include "game_object.h"

#define INITIAL_DIRECTION 91

#define COIN_SCALE Point3f( .1, .1, .1)
#define COIN_1_LOCATION Point3f( 6.0, 1.2, 6.0)
#define COIN_2_LOCATION Point3f( 8.0, 1.2, 6.0)
#define COIN_3_LOCATION Point3f( 10.0, 1.2, 6.0)
#define ROTATION_AXIS Point3f( 0.0, 1.0, 0.0)
#define COIN_ROTATION -0.25

struct Coin
{
	Point3f location;
	float rotation;
	
	Coin( Point3f _location, float _rotation) { location = _location; rotation = _rotation; }
};

class CoinObject: public GameObject
{
	public:
	
		CoinObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color);
		CoinObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId);

		void init();
		void update();
		void draw();
		
		float distanceFrom( GameObject* otherObject);
	
		void collisionHandler(GameObject *gameObject, Collision collision);

	private:
	
		std::vector<Coin> coins;
		
		void rotateCoins();

};

#endif //__COIN_OBJECT_H__
