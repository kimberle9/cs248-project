
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
#include "coin_object.h"
#include "enemy_object.h"
#include "scene.h"

Scene *scene;

PlayerObject *player;
GameObject *environment;
CoinObject *coins;

Point3f cameraNormal = Point3f(0.0, 1.0, 0.0);

Point3f cameraPositionOffset = Point3f(0.0, 0.0, 0.0);
Point3f cameraAimOffset = Point3f(0.0, 0.0, 0.0);

GLuint textures[1];

Point3f getCameraPosition() {
    Point3f playerPosition = player->getPosition();
    Point3f playerDirection = player->getDirection();

    Point3f cameraPosition = Point3f(
        playerPosition.x - (playerDirection.x * 20),
        playerPosition.y + 13,
        playerPosition.z - (playerDirection.z * 20)
    );

    return cameraPositionOffset + cameraPosition;
}

Point3f getCameraAim() {
    return cameraAimOffset + player->getPosition();
}

void updateCamera() {
    Point3f cameraPosition = getCameraPosition();
    Point3f cameraAim = getCameraAim();

	gluLookAt(
        cameraPosition.x, cameraPosition.y, cameraPosition.z, 
        cameraAim.x,      cameraAim.y,      cameraAim.z,
        cameraNormal.x,   cameraNormal.y,   cameraNormal.z
    );
}

void displayCallback() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    scene->update();
    updateCamera();
    scene->draw();

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
    glGenTextures(1, textures);

    scene = new Scene();
    
    player = new PlayerObject("player", "objects/tree.obj", RGBColor(0.0, 1.0, 0.0));
    environment = new GameObject("environment", "environments/textured_environment.obj", "textures/Environment_texture.png", textures[0]);
    
    CoinObject::generateCoins(scene);
    EnemyObject::generateEnemies(scene);
    
    scene->gameObjects.push_back( environment);
    scene->gameObjects.push_back ( player);

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glShadeModel (GL_SMOOTH);
    glEnable( GL_DEPTH_TEST);
}

void printCameraCoords() {
    Point3f cameraPosition = getCameraPosition();
    Point3f cameraAim = getCameraAim();

    std::cout << "Camera position: (" << cameraPosition.x << ", " << cameraPosition.y << ", " << cameraPosition.z << ")" << std::endl;
    std::cout << "Camera aim: (" << cameraAim.x << ", " << cameraAim.y << ", " << cameraAim.z << ")" << std::endl;
    std::cout << "Camera normal: (" << cameraNormal.x << ", " << cameraNormal.y << ", " << cameraNormal.z << ")" << std::endl;
}

void specialKeyCallback( int key, int x, int y) {
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
        case '1': { cameraPositionOffset.x += .5; printCameraCoords(); break; }
        case '2': { cameraPositionOffset.x -= .5; printCameraCoords(); break; }
        case '3': { cameraPositionOffset.y += .5; printCameraCoords(); break; }
        case '4': { cameraPositionOffset.y -= .5; printCameraCoords(); break; }
        case '5': { cameraPositionOffset.z += .5; printCameraCoords(); break; }
        case '6': { cameraPositionOffset.z -= .5; printCameraCoords(); break; }
        case '7': { cameraAimOffset.x += .5; printCameraCoords(); break; }
        case '8': { cameraAimOffset.x -= .5; printCameraCoords(); break; }
        case '9': { cameraAimOffset.y += .5; printCameraCoords(); break; }
        case '0': { cameraAimOffset.y -= .5; printCameraCoords(); break; }
        case '-': { cameraAimOffset.z += .5; printCameraCoords(); break; }
        case '=': { cameraAimOffset.z -= .5; printCameraCoords(); break; }
        case 'r': { 
            cameraPositionOffset = Point3f(0.0, 0.0, 0.0);
            cameraAimOffset = Point3f(0.0, 0.0, 0.0);
            break;
        }
        case 'j': case ' ': { player->jump(); break; }
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
