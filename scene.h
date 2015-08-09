#ifndef __SCENE_H__
#define __SCENE_H__

#include "game_object.h"

#include <vector>

class Scene {
public:
	std::vector<GameObject *> gameObjects;
	
	void update();
	void draw();
};

#endif // __SCENE_H__
