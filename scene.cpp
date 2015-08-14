#include "scene.h"

#include <map>
#include <vector>

#include "findGLUT.h"

#include "game_object.h"
#include "player_object.h"

Scene::Scene() {
    screen = START_SCREEN;
    SCENE_BBOX.partition(partitions, PARTITION_SIZE.x, PARTITION_SIZE.y, PARTITION_SIZE.z);
}

void Scene::update() {
    std::vector<GameObject *> *objects = screenToObjects[screen];
    for (GameObject *object: *objects) {
    	object->update();
    	
    	if ( object->destroyed() )
    	{
    		objects->erase(std::remove(objects->begin(), objects->end(), object), objects->end());
    		continue;
    	}
    }
}

void Scene::draw() {
    std::vector<GameObject *> *objects = screenToObjects[screen];
    for (GameObject *object: *objects) {
        object->draw();
    }
}

void Scene::addObject(int addScreen, GameObject *object) {
    std::vector<GameObject *> *currObjects;
    if (screenToObjects.count(addScreen) == 0) {
        currObjects = new std::vector<GameObject *>();
        screenToObjects.insert(std::pair<int, std::vector<GameObject *> *>(addScreen, currObjects));
    } else {
        currObjects = screenToObjects[addScreen];
    }
    currObjects->push_back(object);
}

void Scene::clearObjects(int screen) {
    std::vector<GameObject *> *objects = screenToObjects[screen];
    objects->clear();
}