#include "scene.h"

#include <map>
#include <vector>

#include "findGLUT.h"

#include "game_object.h"
#include "player_object.h"

#include "triangle_triangle_intersection.h"

extern PlayerObject* player;
extern GameObject* environment;

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

	if (environment->partitionToTriangles.empty()) {
		updateTriangles(environment);
	}

	player->updateX();
	updateTriangles(player);
	testCollision(player, environment);

	player->updateY();
	updateTriangles(player);
	testCollision(player, environment);

	player->updateZ();
	updateTriangles(player);
	testCollision(player, environment);

	for (GameObject *gameObject: gameObjects) {
		gameObject->postUpdate();
	}
}

void Scene::draw() {
    for (GameObject *gameObject: gameObjects) {
    	gameObject->draw();
    }
}

void Scene::testCollision(GameObject *gameObject1, GameObject *gameObject2) {
	bool collided = false;
	for (auto partition: partitions) {
		std::vector<Triangle3f> *triangles1 = gameObject1->partitionToTriangles[partition];
		std::vector<Triangle3f> *triangles2 = gameObject2->partitionToTriangles[partition];
		if (triangles1 != NULL && triangles2 != NULL && !triangles1->empty() && !triangles2->empty()) {
			for (auto &triangle1: *triangles1) {
				for (auto &triangle2: *triangles2) {
					if (triangle1.getBBox().intersects(triangle2.getBBox())) {
						    float p1[3] = { triangle1.a.x, triangle1.a.y, triangle1.a.z };
						    float p2[3] = { triangle1.b.x, triangle1.b.y, triangle1.b.z };
						    float p3[3] = { triangle1.c.x, triangle1.c.y, triangle1.c.z };
						    float q1[3] = { triangle2.a.x, triangle2.a.y, triangle2.a.z };
						    float q2[3] = { triangle2.b.x, triangle2.b.y, triangle2.b.z };
						    float q3[3] = { triangle2.c.x, triangle2.c.y, triangle2.c.z };
						    if (tri_tri_overlap_test_3d( p1, p2, p3, q1, q2, q3) == 1) {
								Collision collision = Collision(triangle1, triangle2);
								gameObject1->revertLastUpdate();
								gameObject1->collisionHandler(gameObject2, collision);
								collided = true;
								break;
						    }

					}
				}
				if (collided) { break; }
			}
			if (collided) { break; }
		}
	}
}

void Scene::updateTriangles(GameObject *gameObject) {
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
