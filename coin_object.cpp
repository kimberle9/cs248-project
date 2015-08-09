#include "coin_object.h"

CoinObject::CoinObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color) :
	GameObject(_name, meshFilePath, _color) 
{
	init();
}

CoinObject::CoinObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId) :
  GameObject(_name, meshFilePath, textureImageFilename, texId) 
{ 
	init();
}

void CoinObject::init() 
{
	Coin coin1 = Coin( COIN_1_LOCATION, rand() % 360);
	coins.push_back( coin1);
	
	Coin coin2 = Coin( COIN_2_LOCATION, rand() % 360);
	coins.push_back( coin2);
	
	Coin coin3 = Coin( COIN_3_LOCATION, rand() % 360);
	coins.push_back( coin3);
	
	setScale( COIN_SCALE);
}

void CoinObject::rotateCoins()
{
	for (int i = 0; i < coins.size(); i++)
	{
		coins[i].rotation += COIN_ROTATION;
		if (0 > coins[i].rotation)
		{
			coins[i].rotation += 360;
		}
	}
}

void CoinObject::update()
{
	rotateCoins();
}

void CoinObject::draw()
{
	//glPushMatrix();
	///glMatrixMode( GL_MODELVIEW);
	//glLoadIdentity();
	
	for (int i = 0; i < coins.size(); i++)
	{
		glPushMatrix();
		//glMatrixMode( GL_MODELVIEW);
		//glLoadIdentity();
		//std::cout << coins[i].location.y << std::endl;
		glTranslatef( coins[i].location.x, coins[i].location.y, coins[i].location.z);
		glScalef(s.x, s.y, s.z);
		glRotatef( coins[i].rotation, ROTATION_AXIS.x, ROTATION_AXIS.y, ROTATION_AXIS.z);

		if (texture != NULL) { texture->bind(); }

		glColor3f(color.r, color.g, color.b);
	
		mesh.draw();

		if (texture != NULL) { texture->unBind(); }
		
		glPopMatrix();
	}
	
	//glPopMatrix();
}

float CoinObject::distanceFrom( GameObject* otherObject)
{
	return 0;
}

void CoinObject::collisionHandler(GameObject *gameObject, Collision collision) {
	return;
}
