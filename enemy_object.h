#ifndef __ENEMY_OBJECT_H__
#define __ENEMY_OBJECT_H__

#include "game_object.h"
#include "scene.h"

#define INITIAL_DIRECTION 91

#define ENEMY_SCALE Point3f( .2, .2, .2)

#define ENEMY_1_LOCATION Point3f( 7.0, 2.5, -11.0)

class EnemyObject: public GameObject
{
	public:
	
		EnemyObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color, Point3f location);
		EnemyObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId, Point3f location);

		void init( Point3f location);
		void update();
		
		float distanceFrom( GameObject* otherObject);
	
		void collisionHandler(GameObject *gameObject, Collision collision);
		
		static void generateEnemies( Scene* scene);

	private:

};

#endif //__ENEMY_OBJECT_H__
