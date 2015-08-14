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
    std::vector<GameObject *> *gameObjects = screenToGameObjects[screen];
    for (GameObject *gameObject: *gameObjects) {
    	gameObject->update();
    	
    	if ( gameObject->destroyed() )
    	{
    		gameObjects->erase(std::remove(gameObjects->begin(), gameObjects->end(), gameObject), gameObjects->end());
    		continue;
    	}
    }
}

void Scene::draw() {
    std::vector<GameObject *> *gameObjects = screenToGameObjects[screen];
    for (GameObject *gameObject: *gameObjects) {
        gameObject->draw();
    }
}

void Scene::addObject(int addScreen, GameObject *gameObject) {
    std::vector<GameObject *> *currGameObjects;
    if (screenToGameObjects.count(addScreen) == 0) {
        currGameObjects = new std::vector<GameObject *>();
        screenToGameObjects.insert(std::pair<int, std::vector<GameObject *> *>(addScreen, currGameObjects));
    } else {
        currGameObjects = screenToGameObjects[addScreen];
    }
    currGameObjects->push_back(gameObject);
}