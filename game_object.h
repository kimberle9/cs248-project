#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <boost/optional.hpp>
#include <vector>
#include <map>

#include "findGLUT.h"
#include "mesh.h"
#include "simple_texture.h"

struct Collision {
	Triangle3f source;
	Triangle3f target;

	Collision(Triangle3f s, Triangle3f t) { source = s; target = t; } 
};

class GameObject {
private:
	// the position of this object before the last update (used to revert on collision)
	Point3f lastT;
	Point3f lastS;
	Point3f lastR; float lastRotationAngle;

protected:
	SimpleTexture *texture = NULL;
	bool _destroyed;

	// gets called before every draw call of this object.
	// should be overriden by sub-classes to update object state (position, rotation, etc).
	virtual void updateHandler(void);

public:
	Mesh mesh;
	Point3f t; // translation vector
	Point3f s; // scale vector
	Point3f r; float rotationAngle; // rotation axis and angle
	RGBColor color;
	std::string name;
	std::map<BBox3f, std::vector<Triangle3f> *> partitionToTriangles;

	GameObject(
		const std::string& _name, 
		const std::string& meshFilePath, 
		RGBColor _color
	);

	GameObject(
		const std::string& _name,
		const std::string& meshFilePath,
		const std::string& textureImageFilename,
		GLuint texId
	);

	// common initialization code
	void init(
		const std::string& _name, 
		const std::string& meshFilePath
	); 

	void setScale(Point3f s);
	void setTranslation(Point3f _t);
	void setRotation(float _angle, Point3f _r);
	void rotate(float _angle);

	Point3f getPosition();
	float distanceFrom( GameObject* otherObject);
	float horizontalDistanceFrom( GameObject* otherObject);
	float verticalDistanceFrom( GameObject* otherObject);
	bool destroyed();

	// gets called during every OpenGL draw call.
	// this method should not be overriden by sub-classes (override updateHandler instead)
	// returns whether the objects position changed.
	bool update(void);

	// gets called during every OpenGL draw call after GameObject::update.
	// this method should not be overriden by sub-classes (use setTranslation, setRotation, etc, instead)
	void draw(void);

	// gets called by the scene when this object's last update caused it to
	// collide with another. the translation, scale, and rotation vectors
	// are reverted to their state prior to the last update
	void revertLastUpdate(void);

	// gets called when this object collides with another. 
	// can be overriden by sub-classes. params:
	//   1. gameObject: the colliding object
	//   2. collision:  struct containing the specific triangles that intersected
	virtual void collisionHandler(GameObject *gameObject, Collision collision);
};

#endif // __GAME_OBJECT_H__
