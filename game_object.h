#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "findGLUT.h"
#include "mesh.h"
#include "simple_texture.h"

class GameObject {
protected:
	Mesh mesh;
	SimpleTexture *texture;

public:
	Point3f t; // translation vector
	RGBColor color;
	GameObject(const std::string& meshFilename, RGBColor color);
	GameObject(GLuint texId, const std::string& meshFilename, const std::string& textureImageFilename);
	
	bool intersects(GameObject *o);
	void translateX(float _tx);
	void translateY(float _ty);
	void translateZ(float _tz);
	
	virtual void animate( void);
	virtual void draw();
};

#endif // __GAME_OBJECT_H__
