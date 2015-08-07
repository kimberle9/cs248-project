#include "game_object.h"

#include "findGLUT.h"
#include "simple_image.h"
#include "simple_texture.h"

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
	rotationAngle = 0;
	name = _name;
	mesh.loadData(meshFilePath);
	_destroyed = false;
}

bool GameObject::update() {
	lastT = t;
	lastS = s;
	lastR = r; 
	lastRotationAngle = rotationAngle;
	updateHandler();
	// TODO: take into account changes in s, r, and rotationAngle
	return !(t == lastT);
}

void GameObject::revertLastUpdate() {
	t = lastT;
	s = lastS;
	r = lastR; 
	rotationAngle = lastRotationAngle;
}

void GameObject::draw() {
	glPushMatrix();

	glTranslatef(t.x, t.y, t.z);
	glScalef(s.x, s.y, s.z);

	if (rotationAngle != 0) {
		glRotatef(rotationAngle, r.x, r.y, r.z);
	}

	if (texture != NULL) { texture->bind(); }

	glColor3f(color.r, color.g, color.b);
	
	mesh.draw();

	if (texture != NULL) { texture->unBind(); }

	glPopMatrix();
}

float GameObject::distanceFrom( GameObject* otherObject)
{
	float result = 0;
	
	Point3f otherLoc = otherObject->getPosition();
	float dx = t.x - otherLoc.x;
	float dy = t.y - otherLoc.y;
	float dz = t.z - otherLoc.z;
	
	result = sqrt( dx * dx + dz * dz + dy * dy);
	
	return result;
}

float GameObject::horizontalDistanceFrom( GameObject* otherObject)
{
	float result = 0;
	
	Point3f otherLoc = otherObject->getPosition();
	float dx = t.x - otherLoc.x;
	float dz = t.z - otherLoc.z;
	
	result = sqrt( dx * dx + dz * dz);
	
	return result;
}

float GameObject::verticalDistanceFrom( GameObject* otherObject)
{
	float result = 0;
	
	Point3f otherLoc = otherObject->getPosition();
	
	result = abs( t.y - otherLoc.y);
	
	return result;
}

bool GameObject::destroyed()
{
	return _destroyed;
}

void GameObject::setScale(Point3f _s) { s = _s; }
void GameObject::setTranslation( Point3f _t) { t = _t; }
void GameObject::setRotation(float _angle, Point3f _r) { rotationAngle = _angle; r = _r; }
void GameObject::rotate(float _angle) { rotationAngle += _angle; }

Point3f GameObject::getPosition() {
	return t;
}

void GameObject::updateHandler() {
	return;
}

void GameObject::collisionHandler(GameObject *gameObject, Collision collision) {
	return;
}
