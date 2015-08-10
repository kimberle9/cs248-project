#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <boost/optional.hpp>

#include "findGLUT.h"
#include "mesh.h"
#include "simple_texture.h"

struct Collision {
	Triangle3f source;
	Triangle3f target;

	Collision(Triangle3f s, Triangle3f t) { source = s; target = t; } 
};

class GameObject {
protected:
	Mesh mesh;
	SimpleTexture *texture = NULL;

public:
	Point3f t; // translation vector
	Point3f s; // scale vector
	Point3f r; float rotationAngle; // rotation axis and angle
	RGBColor color;
	std::string name;
	
	GameObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color);
	GameObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId);
	void init(const std::string& _name, const std::string& meshFilePath); // common initialization code
	
	void setScale(Point3f s);
	void setTranslation(Point3f _t);
	void setRotation(float _angle, Point3f _r);
	void rotate(float _angle);

	Point3f getPosition();

	boost::optional<Collision> getCollision(GameObject *o);

	virtual void update( void);
	virtual void draw( void);

	// this function gets called when this object collides with another.
	// params:
	//   1. gameObject: the colliding object
	//   2. collision:  struct containing the specific triangles that intersected
	virtual void collisionHandler(GameObject *gameObject, Collision collision); 
};

#endif // __GAME_OBJECT_H__
