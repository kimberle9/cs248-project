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
	SimpleTexture *texture;

public:
	Point3f t; // translation vector
	Point3f s; // scale vector
	RGBColor color;
	std::string name;
	
	GameObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color);
	GameObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId);
	void init(const std::string& _name, const std::string& meshFilePath); // common initialization code
	
	void setScale(Point3f s);

	boost::optional<Collision> getCollision(GameObject *o);

	virtual void update( void);
	virtual void draw();

	// this function gets called when this object collides with another.
	// params:
	//   1. gameObject: the colliding object
	//   2. collision:  struct containing the specific triangles that intersected
	virtual void collisionHandler(GameObject *gameObject, Collision collision); 
};

#endif // __GAME_OBJECT_H__
