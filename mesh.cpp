#include <fstream>
#include <iostream>

#include "findGLUT.h"

#include "mesh.h"

const float EPS = .0000001;

bool Mesh::loadData(const std::string& filename) {
	vertices.clear();
    text_coords.clear();
    faces.clear();

    std::ifstream ifs(filename.c_str());

    for (std::string line; std::getline(ifs, line);) {
		if (line.size() > 1) {
			switch (line.at(0)) {
				case 'v': {
					switch (line.at(1)) {
						case ' ': {
							float x, y, z;
							sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
							vertices.push_back(Point3f(x, y, z));
							break;
						}
						case 't': {
							float u, v;
							sscanf(line.c_str(), "vt %f %f", &u, &v);
							text_coords.push_back(Point3f(u, v, 0.0));
							break;
						}
						default: { break; }
		    	    }
		    	    break;
		    	}
		    	case 'f': {
					char a[20], b[20], c[20];
					sscanf(line.c_str(), "f %s %s %s", a, b, c);

					Point3f f1 = parse_face_entry(a);
					Point3f f2 = parse_face_entry(b);
					Point3f f3 = parse_face_entry(c);

					if (f1.x == -1 || f2.x == -1 || f3.x == -1) {
				    	std::cerr << "Error parsing line in " << filename << ": " << line << std::endl;
				    	return false;
					}

					Point3f v1 = vertices[f1.x - 1];
					Point3f v2 = vertices[f2.x - 1];
					Point3f v3 = vertices[f3.x - 1];

					if ((v1 - v2).magnitude() < EPS || (v1 - v3).magnitude() < EPS|| (v2 - v3).magnitude() < EPS) {
				    	std::cout << "Skipping invalid face in " << filename << ": " << line << std::endl;
				    } else {
			    	    if (f1.y == -1) {
							faces.push_back(Triangle3f(vertices[f1.x - 1], vertices[f2.x - 1], vertices[f3.x - 1]));
			    	    } else {
							faces.push_back(Triangle3f(
								vertices[f1.x - 1], vertices[f2.x - 1], vertices[f3.x - 1],
								vertices[f1.y - 1], vertices[f2.y - 1], vertices[f3.y - 1]
							));
			    	    }
			    	}
		    	    break;
		    	}
		    	default: { break; }
	    	}
	    }
	}
    return true;
}

Point3f Mesh::parse_face_entry(char *entry) {
    int a, b, c;
    if (sscanf(entry, "%d/%d/%d", &a, &b, &c) == 3) {
    	return Point3f(a, b, -1);
    } else if (sscanf(entry, "%d/%d", &a, &b) == 2) {
    	return Point3f(a, b, -1);
    } else if (sscanf(entry, "%d//%d", &a, &c) == 2) {
    	return Point3f(a, -1, -1);
    } else if (sscanf(entry, "%d", &a) == 1) {
    	return Point3f(a, -1, -1);
    } else {
    	return Point3f(-1, -1, -1);
    }
}

void Mesh::draw() {
    for (Triangle3f face : faces) {
        glBegin(GL_TRIANGLES);

        Point3f normal = face.normal().normalize();
        glNormal3f(normal.x, normal.y, normal.z);

        if (face.t_a.is_initialized()) {
    	    glTexCoord2f(face.t_a->x, face.t_a->y);
        }
        glVertex3f(face.a.x, face.a.y, face.a.z);

        if (face.t_b.is_initialized()) {
    	    glTexCoord2f(face.t_b->x, face.t_b->y);
        }
        glVertex3f(face.b.x, face.b.y, face.b.z);

        if (face.t_c.is_initialized()) {
    	    glTexCoord2f(face.t_c->x, face.t_c->y);
        }
        glVertex3f(face.c.x, face.c.y, face.c.z);
        
        glEnd();
    }
}