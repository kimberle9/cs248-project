
#include "main.h"
#ifdef WIN32
#define ssize_t SSIZE_T
#endif

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cmath>

#include "mesh.h"
#include "game_object.h"
#include "player_object.h"

std::vector<GameObject *> gameObjects;
PlayerObject *player;
GameObject *environment;

Point3f cameraPosition = Point3f(50.0, 8.0, 1);
Point3f cameraAim = Point3f(-31.0, 6.0, -4.5);
Point3f cameraNormal = Point3f(0.0, 1.0, 0.0);

void updateCamera()
{
	Point3f playerPosition = player->getPosition();
	Point3f playerDirection = player->getDirection();
	
	cameraPosition.x = playerPosition.x - (playerDirection.x * 20);
	cameraPosition.z = playerPosition.z - (playerDirection.z * 20);
	
	cameraAim.x = playerPosition.x;
	cameraAim.z = playerPosition.z;
	cameraAim.y = playerPosition.y;

	gluLookAt(
        cameraPosition.x, cameraPosition.y, cameraPosition.z, 
        cameraAim.x,      cameraAim.y,      cameraAim.z,
        cameraNormal.x,   cameraNormal.y,   cameraNormal.z
    );
}

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    
    for (GameObject *gameObject: gameObjects) {
    	gameObject->animate();
    }

    updateCamera();
    
    for (GameObject *gameObject: gameObjects) {
        gameObject->draw();
    }

    // if (player->intersects(environment)) {
    //     player->color = RGBColor(1.0, 0.0, 0.0);
    // } else {
    //     player->color = RGBColor(0.0, 1.0, 0.0);
    // }

    glutSwapBuffers();
}

void reshapeCallback(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(30.0f, (float)w/(float)h, 0.1f, 100000.f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void setup() {
    GLuint textures[1];
    glGenTextures(1, textures);

    player = new PlayerObject("objects/tree.obj", RGBColor(0.0, 1.0, 0.0));
    environment = new GameObject(textures[0], "environments/textured_environment.obj", "textures/Environment_texture.png");
    gameObjects.push_back(environment);
    gameObjects.push_back(player);
    // gameObjects.push_back(new GameObject(textures[0], "objects/mushroom.obj", "objects/mushroom.png"));

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glShadeModel (GL_SMOOTH);
}

void printCameraCoords() {
    std::cout << "Camera position: (" << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << ")" << std::endl;
    std::cout << "Camera aim: (" << cameraAim.x << ", " << cameraAim.y << ", " << cameraAim.z << ")" << std::endl;
    std::cout << "Camera normal: (" << cameraNormal.x << ", " << cameraNormal.y << ", " << cameraNormal.z << ")\n" << std::endl;
}

void specialKeyCallback( int key, int x, int y)
{
	switch( key)
	{
		case GLUT_KEY_UP: { player->step( 1.0); break; }
		case GLUT_KEY_DOWN: { player->step( -1.0); break; }			
		case GLUT_KEY_LEFT: { player->turnLeft(); break; }
		case GLUT_KEY_RIGHT: { player->turnRight(); break; }	
		default: break;
	}
	
	glutPostRedisplay();

	return;
}

void keyCallback(unsigned char key, int x, int y) {
    switch(key) {
        case 'q': { exit(0); break; }
        case '1': { cameraPosition.x += .5; printCameraCoords(); break; }
        case '2': { cameraPosition.x -= .5; printCameraCoords(); break; }
        case '3': { cameraPosition.y += .5; printCameraCoords(); break; }
        case '4': { cameraPosition.y -= .5; printCameraCoords(); break; }
        case '5': { cameraPosition.z += .5; printCameraCoords(); break; }
        case '6': { cameraPosition.z -= .5; printCameraCoords(); break; }
        case '7': { cameraAim.x += .5; printCameraCoords(); break; }
        case '8': { cameraAim.x -= .5; printCameraCoords(); break; }
        case '9': { cameraAim.y += .5; printCameraCoords(); break; }
        case '0': { cameraAim.y -= .5; printCameraCoords(); break; }
        case '-': { cameraAim.z += .5; printCameraCoords(); break; }
        case '=': { cameraAim.z -= .5; printCameraCoords(); break; }
        case 'f': { player->translateX(.5); break; }
        case 's': { player->translateX(-.5); break; }
        case 'e': { player->translateY(.5); break; }
        case 'd': { player->translateY(-.5); break; }
        case 'x': { player->translateZ(.5); break; }
        case 'c': { player->translateZ(-.5); break; }
        case 'j': { player->jump(); break; }
        default: { break; }
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    // Initialize GLUT.
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(20, 20);
    glutInitWindowSize(1280, 960);
    glutCreateWindow("Mario Game");

    //
    // Initialize GLEW.
    //
#if !defined(__APPLE__) && !defined(__linux__)
    glewInit();
    if(!GLEW_VERSION_2_0) {
        printf("Your graphics card or graphics driver does\n"
               "\tnot support OpenGL 2.0, trying ARB extensions\n");

        if(!GLEW_ARB_vertex_shader || !GLEW_ARB_fragment_shader) {
            printf("ARB extensions don't work either.\n");
            printf("\tYou can try updating your graphics drivers.\n"
                   "\tIf that does not work, you will have to find\n");
            printf("\ta machine with a newer graphics card.\n");
            exit(1);
        }
    }
#endif

    setup();

    glutDisplayFunc(displayCallback);
    glutReshapeFunc(reshapeCallback);
    glutKeyboardFunc(keyCallback);
    glutSpecialFunc(specialKeyCallback);
    glutIdleFunc(displayCallback);

    glutMainLoop();
    return 0;
}
