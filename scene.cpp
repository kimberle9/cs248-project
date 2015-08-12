#include "scene.h"

#include <map>
#include <vector>

#include "findGLUT.h"

#include "game_object.h"
#include "player_object.h"

Scene::Scene() {
	SCENE_BBOX.partition(partitions, PARTITION_SIZE.x, PARTITION_SIZE.y, PARTITION_SIZE.z);
}

void Scene::update() {
    for (GameObject *gameObject: gameObjects) {
    	gameObject->update();
    	
    	if ( gameObject->destroyed() )
    	{
    		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObject), gameObjects.end());
    		continue;
    	}
    }
}

void Scene::draw() {
    for (GameObject *gameObject: gameObjects) {
    	gameObject->draw();
    }
}