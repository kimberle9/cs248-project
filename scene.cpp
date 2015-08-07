#include "scene.h"

#include <map>
#include <vector>

#include "findGLUT.h"

#include "game_object.h"

Scene::Scene() {
	SCENE_BBOX.partition(partitions, PARTITION_SIZE.x, PARTITION_SIZE.y, PARTITION_SIZE.z);
}

void Scene::update() {
	std::map<GameObject *, bool> wasUpdated;
    for (GameObject *gameObject: gameObjects) {
    	bool updated = gameObject->update();
    	
    	if ( gameObject->destroyed() )
    	{
    		gameObjects.erase(std::remove(gameObjects.begin(), gameObjects.end(), gameObject), gameObjects.end());
    		continue;
    	}
    	
    	wasUpdated.insert(std::pair<GameObject *, bool>(gameObject, updated));
    }

    for (auto gameObject : gameObjects) {
    	bool updated = wasUpdated[gameObject];

    	if (updated || gameObject->partitionToTriangles.empty()) {
    		gameObject->partitionToTriangles.clear();
			for (auto &face : gameObject->mesh.faces) {
				Triangle3f faceT = face * gameObject->s;
				faceT.add(gameObject->t);
				for (auto partition: partitions) {
					std::vector<Triangle3f> *currTriangles;
					if (gameObject->partitionToTriangles.count(partition) == 0) {
						currTriangles = new std::vector<Triangle3f>();
						gameObject->partitionToTriangles.insert(std::pair<BBox3f, std::vector<Triangle3f> *>(partition, currTriangles));
					} else {
						currTriangles = gameObject->partitionToTriangles[partition];
					}
					if (partition.intersects(faceT.getBBox())) {
						currTriangles->push_back(faceT);
					}
				}
			}
		}
	}

	std::vector<GameObject *> gameObjectsToTest = gameObjects;
	while (!gameObjectsToTest.empty()) {
		GameObject *gameObject1 = gameObjectsToTest.back();
		gameObjectsToTest.pop_back();
		if (wasUpdated[gameObject1]) {
			bool collided = false;
			for (auto gameObject2: gameObjectsToTest) {
				for (auto partition: partitions) {
					std::vector<Triangle3f> *triangles1 = gameObject1->partitionToTriangles[partition];
					std::vector<Triangle3f> *triangles2 = gameObject2->partitionToTriangles[partition];
					if (triangles1 != NULL && triangles2 != NULL && !triangles1->empty() && !triangles2->empty()) {
						for (auto &triangle1: *triangles1) {
							for (auto &triangle2: *triangles2) {
								if (triangle1.getBBox().intersects(triangle2.getBBox())) {
									Collision collision = Collision(triangle1, triangle2);
									gameObject1->revertLastUpdate();
									gameObject1->collisionHandler(gameObject2, collision);
									collided = true;
									break;
								}
							}
							if (collided) { break; }
						}
					}
					if (collided) { break; }
				}
				if (collided) { break; }
			}
		}
	}
}

void Scene::draw() {
    for (GameObject *gameObject: gameObjects) {
    	gameObject->draw();
    }
}
