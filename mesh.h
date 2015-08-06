#ifndef __MESH_H__
#define __MESH_H__

#include <boost/optional.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <math.h>

struct Point3f {
	float x, y, z;

	Point3f() { x = 0.; y = 0.; z = 0.; };
	Point3f(float _x, float _y, float _z) { x = _x; y = _y; z = _z; };

    Point3f operator+(Point3f o) { 
    	return Point3f(x+o.x, y+o.y, z+o.z); 
    }

    Point3f operator-(Point3f o) { 
    	return Point3f(x-o.x, y-o.y, z-o.z); 
    }

    Point3f cross(Point3f o) {
    	return Point3f(y * o.z - o.y * z, o.x * z - x * o.z, x * o.y - o.x * y); 
    }

    float magnitude() {
		return sqrt(x * x + y * y + z * z);
    }

    Point3f normalize() {
		float mag = magnitude();
		return Point3f(x / mag, y / mag, z / mag);
    }
};

struct Triangle3f {
	Point3f a, b, c;
	boost::optional<Point3f> t_a, t_b, t_c;

	Triangle3f() { 
		a = Point3f(); b = Point3f(); c = Point3f(); 
		t_a = boost::none; t_b = boost::none; t_c = boost::none;
	};
	Triangle3f(Point3f _a, Point3f _b, Point3f _c) { 
		a = _a; b = _b; c = _c; 
		t_a = boost::none; t_b = boost::none; t_c = boost::none;
	};
	Triangle3f(Point3f _a, Point3f _b, Point3f _c, Point3f _t_a, Point3f _t_b, Point3f _t_c) { 
		a = _a; b = _b; c = _c; 
		t_a = _t_a; t_b = _t_b; t_c = _t_c; 
	};

    Triangle3f operator+(Point3f p) { 
    	return Triangle3f(a + p, b + p, c + p); 
    }

	Point3f normal() { 
		return (b - a).cross(c - a); 
	}
};

class Mesh {
private:
	std::vector<Point3f> vertices;
	std::vector<Point3f> text_coords;
	Point3f parse_face_entry(char *entry);

public:
	std::vector<Triangle3f> faces;
	Mesh() { vertices = std::vector<Point3f>(); text_coords = std::vector<Point3f>(); faces = std::vector<Triangle3f>(); };
	bool loadData(const std::string& filename);
	void draw();
};

#endif // __GAME_OBJECTS_H__