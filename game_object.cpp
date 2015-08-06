#include "game_object.h"

#include "findGLUT.h"
#include "simple_image.h"
#include "simple_texture.h"

#include "triangle_triangle_intersection.h"

GameObject::GameObject(const std::string& meshFilename, RGBColor _color) {
	mesh.loadData(meshFilename);
	texture = NULL;
	color = _color;
	t = Point3f();
}

GameObject::GameObject(GLuint texId, const std::string& meshFilename, const std::string& textureImageFilename) { 
	mesh.loadData(meshFilename);
	SimpleImage img = SimpleImage(textureImageFilename);
	texture = new SimpleTexture(texId, &img);
	color = RGBColor();
	t = Point3f();
}

void GameObject::draw() {
	glPushMatrix();

	glColor3f(color.r, color.g, color.b);

    glTranslatef(t.x, t.y, t.z);

	if (texture != NULL) { texture->bind(); }
	mesh.draw();
	if (texture != NULL) { texture->unBind(); }

	glPopMatrix();
}

void GameObject::translateX(float tx) { t.x += tx; }
void GameObject::translateY(float ty) { t.y += ty; }
void GameObject::translateZ(float tz) { t.z += tz; }

bool GameObject::intersects(GameObject *o) {
    for (Triangle3f face : mesh.faces) {
    	for (Triangle3f oFace : o->mesh.faces) {
    		Triangle3f faceT = face + t;
    		Triangle3f oFaceT = oFace + o->t;
		    float p1[3] = { faceT.a.x, faceT.a.y, faceT.a.z };
		    float p2[3] = { faceT.b.x, faceT.b.y, faceT.b.z };
		    float p3[3] = { faceT.c.x, faceT.c.y, faceT.c.z };
		    float q1[3] = { oFaceT.a.x, oFaceT.a.y, oFaceT.a.z };
		    float q2[3] = { oFaceT.b.x, oFaceT.b.y, oFaceT.b.z };
		    float q3[3] = { oFaceT.c.x, oFaceT.c.y, oFaceT.c.z };
		    if (tri_tri_overlap_test_3d( p1, p2, p3, q1, q2, q3) == 1) {
		    	return true;
		    }
    	}
    }
    return false;
}

void GameObject::animate()
{
	return;
}
