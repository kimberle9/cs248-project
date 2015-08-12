#ifndef __SCENE_H__
#define __SCENE_H__

#include "game_object.h"
#include "mesh.h"

#include <vector>

#define SCENE_BBOX BBox3f(Point3f(-26, -2, -26), Point3f(26, 26, 26))
#define PARTITION_SIZE Point3f(2, 2, 2)

class Scene {
public:
	std::vector<GameObject *> gameObjects;
	std::vector<BBox3f> partitions;

	Scene();
	void update();
	void draw();
};

#endif // __SCENE_H__
