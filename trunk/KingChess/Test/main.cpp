/**
 * This program show on how to use timer function in OpenGL
 * 
 * For more tutorial, see:
 */

#include <Windows.h>
#include <GL/freeglut.h>

#include <ctime>
#include <cstdlib>

#include <iostream>
#include "Input/Mouse.h"
#include "Control/Camera.h"
#include "Control/Graphic.h"
#include "Sences/GameSence.h"

using namespace std;

void initGL(){
	glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

	glClearColor(0.3, 0.3, 0.3, 1);                   // background color
	glClearStencil(0);                          // clear stencil buffer
	glClearDepth(1.0f);                         // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);//Passes if the incoming depth value is greater than or equal to the stored depth value.

	// enable /disable features
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);

	//Lighting
	Light::inst().setPosition(GameScene::inst().lightPosition[0], GameScene::inst().lightPosition[1], 
		GameScene::inst().lightPosition[2], GameScene::inst().lightPosition[3]);
}

void display(){
	glStencilMask(0xffffffff);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	
	glClearStencil(0x4);
	
	glPushMatrix();
	glBegin(GL_LINES);
	
	for(int i = 0; i < 100; i++){
		glColor3f(1, 0, 0);
		glVertex3f(-100, -8, -100 + 2*i);
		glVertex3f(100, -8, -100 + 2*i);

		glColor3f(0, 0, 1);
		glVertex3f(-100 + 2*i, -8, -100);
		glVertex3f(-100 + 2*i, -8, 100);
	}

	glColor3f(0, 1, 0);
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
	
	glEnd();
	GameScene::inst().loop();
	glPopMatrix();

	glutSwapBuffers(); 
}

void idleCB(){
	glutPostRedisplay();
}

void reshapeCB(int width, int height) {
	Graphic::inst().screenWidth = width;
	Graphic::inst().screenHeight = height;

	float aspect = double(width)/double(height);

	// set viewport to be the entire window
	glViewport(0, 0, width, height);

	// set perspective viewing frustum
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-Graphic::inst().near_height * aspect, 
		Graphic::inst().near_height * aspect, 
		-Graphic::inst().near_height,
		Graphic::inst().near_height,
		Graphic::inst().zNear,
		Graphic::inst().zFar);

	// switch to modelview matrix in order to set scene
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(Camera::inst().eye.x, Camera::inst().eye.y, Camera::inst().eye.z,
		Camera::inst().at.x, Camera::inst().at.y, Camera::inst().at.z,
		0, 1, 0 );
}

void mouseCB(int button, int stat, int x, int y){
	Mouse::inst().processMouse(button, stat, x, y);
}

void keyboardCB(unsigned char key, int x, int y){
	printf("Press %c % d %d\n", key, x, y);
	switch (key)
	{
	case 's':
		Camera::inst().zoom(1);
		break;
	case 'l':
		Camera::inst().zoom(-1);
		break;
	default:
		GameScene::inst().processKeyBoard(key, x, y);
	}
	glutPostRedisplay();
}

void mouseMotionCB(int x, int y){
	Mouse::inst().processMouseMotion(x, y);
}

void mousePassiveMotionCB(int x, int y){
	Mouse::inst().processMousePassiveMotion(x, y);
}



int main(int argc, char *argv[]){


    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE | GLUT_STENCIL);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Chess Application");

    initGL();

    glutDisplayFunc(display);
	glutReshapeFunc(reshapeCB);
	glutIdleFunc(idleCB);
	glutMouseFunc(mouseCB);
	glutKeyboardFunc(keyboardCB);
	glutMouseFunc(mouseCB);
	glutMotionFunc(mouseMotionCB);
	glutPassiveMotionFunc(mousePassiveMotionCB);

	glutMainLoop();
    return 0;
}
