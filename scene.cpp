#include "scene.h"

#include "findGLUT.h"

#include "game_object.h"

void Scene::update() {
    for (GameObject *gameObject: gameObjects) {
		Point3f oldT = gameObject->t;
    	gameObject->update();
    	if (!(oldT == gameObject->t)) {
			for (GameObject *otherGameObject: gameObjects) {
				if (gameObject != otherGameObject) {
					boost::optional<Collision> collision = gameObject->getCollision(otherGameObject);
					if (collision.is_initialized()) {
			    		gameObject->t = oldT;
			    		gameObject->collisionHandler(otherGameObject, collision.get());
			    		break;
			    	}
				}
			}
	    }
    }
}

void Scene::draw() {
    for (GameObject *gameObject: gameObjects) {
    	gameObject->draw();
    }
}