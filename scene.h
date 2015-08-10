#ifndef __SCENE_H__
#define __SCENE_H__

#include "game_object.h"
#include "mesh.h"

#include <vector>

#define SCENE_BBOX BBox3f(Point3f(-30, -5, -30), Point3f(30, 30, 30))
#define PARTITION_SIZE Point3f(5, 5, 5)

class Scene {
public:
	std::vector<GameObject *> gameObjects;
	std::vector<BBox3f> partitions;

	Scene();
	void update();
	void draw();
};

#endif // __SCENE_H__
