#ifndef __ENEMY_OBJECT_H__
#define __ENEMY_OBJECT_H__

#include "game_object.h"
#include "scene.h"

#define INITIAL_DIRECTION 91
#define ATTACK_SPEED 0.3
#define ATTACK_DISTANCE 7.0
#define EXPLODE_DISTANCE 0.25
#define MIN_VERTICAL_DY 0.176

#define ENEMY_SCALE Point3f( .2, .2, .2)

#define ENEMY_1_LOCATION Point3f( 7.0, 2.5, -11.0)
#define ENEMY_2_LOCATION Point3f( -5.0, 4.3, 6.0)

class EnemyObject: public GameObject
{
	public:
	
		EnemyObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color, Point3f location);
		EnemyObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId, Point3f location);

		void init( Point3f location);
		void update();
	
		void collisionHandler(GameObject *gameObject, Collision collision);
		
		static void generateEnemies( Scene* scene);

	private:
	
		Point3f direction;
		float speed;
		
		void disable();
		void explode();

};

#endif //__ENEMY_OBJECT_H__
