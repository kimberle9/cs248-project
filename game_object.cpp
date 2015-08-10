#include "game_object.h"

#include <libgen.h>

#include "findGLUT.h"
#include "simple_image.h"
#include "simple_texture.h"

#include "triangle_triangle_intersection.h"

GameObject::GameObject(const std::string& _name, const std::string& meshFilePath, RGBColor _color) {
	init(_name, meshFilePath);
	color = _color;
}

GameObject::GameObject(const std::string& _name, const std::string& meshFilePath, const std::string& textureImageFilename, GLuint texId) {
	init(_name, meshFilePath);
	SimpleImage img = SimpleImage(textureImageFilename);
	texture = new SimpleTexture(texId, &img, SimpleTexture::kNone);
}

void GameObject::init(const std::string& _name,  const std::string& meshFilePath) {
	s = Point3f(1.0, 1.0, 1.0);
	name = _name;
	mesh.loadData(meshFilePath);
}

void GameObject::draw() {
	glPushMatrix();

	glTranslatef(t.x, t.y, t.z);
	glScalef(s.x, s.y, s.z);
	glRotatef(rotationAngle, r.x, r.y, r.z);

	if (texture != NULL) { texture->bind(); }

	glColor3f(color.r, color.g, color.b);
	
	mesh.draw();

	if (texture != NULL) { texture->unBind(); }

	glPopMatrix();
}

void GameObject::setScale(Point3f _s) { s = _s; }
void GameObject::setTranslation( Point3f _t) { t = _t; }
void GameObject::setRotation(float _angle, Point3f _r) { rotationAngle = _angle; r = _r; }
void GameObject::rotate(float _angle) { rotationAngle += _angle; }

Point3f GameObject::getPosition()
{
	return t;
}

boost::optional<Collision> GameObject::getCollision(GameObject *o) {
	for (auto &face : mesh.faces) {
		Triangle3f faceT = face * s;
		faceT.addMutate(t);
		for (auto &oFace : o->mesh.faces) {
			Triangle3f oFaceT = oFace * o->s;
			oFaceT.addMutate(o->t);
			if (faceT.getBBox().intersects(oFaceT.getBBox())) {
				return Collision(faceT, oFaceT);
			}
		}
	}

    return boost::none;
}

void GameObject::update() {
	return;
}

void GameObject::collisionHandler(GameObject *gameObject, Collision collision) {
}
