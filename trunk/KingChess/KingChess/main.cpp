/*
*	main.cpp: program start from here
*/
#include <windows.h>
#include "GL/freeglut.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include "Light.h"
#include "Timer.h"
#include "Graphic.h"
#include "Camera.h"
#include "GameSence.h"
#include "InputManager.h"

using namespace std;

void displayCB();
void reshapeCB(int w, int h);
void idleCB();
void timerCB(int millisec);
void keyboardCB(unsigned char key, int x, int y);
void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);
void mousePassiveMotionCB(int x, int y);

const int   SCREEN_WIDTH    = 800;
const int   SCREEN_HEIGHT   = 600;
const float CAMERA_DISTANCE = 10.0f;
const int   TEXT_WIDTH      = 8;
const int   TEXT_HEIGHT     = 18;
const float DELTA_TIME      = 33;

Timer mTimer;
float color[4] = {1,1,1,1};
void* font = GLUT_BITMAP_HELVETICA_18;
double currentTime = 0;

GLfloat zoomX = 1.0, zoomY = 1.0, zoomZ = 1.0;

///////////////////////////////////////////////////////////////////////////////
// initialize global variables
///////////////////////////////////////////////////////////////////////////////
bool initSharedMem()
{
	Graphic::inst().screenWidth = SCREEN_WIDTH;
	Graphic::inst().screenHeight = SCREEN_HEIGHT;
	return true;
}

///////////////////////////////////////////////////////////////////////////////
// initialize GLUT for windowing
///////////////////////////////////////////////////////////////////////////////
int initGLUT(int argc, char **argv)
{
	// GLUT stuff for windowing
	// initialization openGL window.
	// it is called before any other GLUT routine
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);   // display mode



	glutInitWindowSize(Graphic::inst().screenWidth, Graphic::inst().screenHeight);  // window size
	glutInitWindowPosition(400, 100);               // window location

	// finally, create a window with openGL context
	// Window will not displayed until glutMainLoop() is called
	// it returns a unique ID
	int handle = glutCreateWindow("Assignment - CG. Co Vua");     // param is the title of window

	// register GLUT callback functions
	glutDisplayFunc(displayCB);
	glutTimerFunc(DELTA_TIME, timerCB, 0);             // redraw only every given millisec
	glutReshapeFunc(reshapeCB);
	glutIdleFunc(idleCB);
	glutKeyboardFunc(keyboardCB);
	glutMouseFunc(mouseCB);
	glutMotionFunc(mouseMotionCB);
	glutPassiveMotionFunc(mousePassiveMotionCB);

	return handle;
}

///////////////////////////////////////////////////////////////////////////////
// initialize OpenGL
// disable unused features
///////////////////////////////////////////////////////////////////////////////
void initGL()
{
	glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

	// enable /disable features
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);


	glClearColor(0.3, 0.3, 0.3, 1);                   // background color
	glClearStencil(0);                          // clear stencil buffer
	glClearDepth(1.0f);                         // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);

	Light::inst().setPosition(GameScene::inst().lightPosition[0], GameScene::inst().lightPosition[1], 
		GameScene::inst().lightPosition[2], GameScene::inst().lightPosition[3]);

	float _position[4] = {0, 0, 5, 1};
	float _ambient[4] = {0.2, 0.2, 0.2, 1.0};
	float _diffuse[4] = {0.7, 0.7, 0.7, 1.0};
	float _specular[4] = {1.0, 1.0, 1.0, 1.0};

	glLightfv(GL_LIGHT1, GL_POSITION, _position);
	glLightfv(GL_LIGHT1, GL_AMBIENT,  _ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE,  _diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, _specular);
}

void showInfo(float elapse)
{
	// backup current model-view matrix
	glPushMatrix();                     // save current modelview matrix
	glLoadIdentity();                   // reset modelview matrix

	// set to 2D orthogonal projection
	glMatrixMode(GL_PROJECTION);        // switch to projection matrix
	glPushMatrix();                     // save current projection matrix
	glLoadIdentity();                   // reset projection matrix
	gluOrtho2D(0, Graphic::inst().screenWidth, 0, Graphic::inst().screenHeight); // set to orthogonal projection

	float color[4] = {1, 1, 1, 1};

	stringstream ss;
	ss << std::fixed << std::setprecision(3);

	ss << elapse << ends;
	Graphic::inst().drawString(ss.str().c_str(), 10, Graphic::inst().screenHeight-TEXT_HEIGHT, color, font);
	ss.str("");

	ss << int(1/elapse) << ends;
	Graphic::inst().drawString(ss.str().c_str(), 10, Graphic::inst().screenHeight-(2*TEXT_HEIGHT), color, font);
	ss.str("");

	// unset floating format
	ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);

	// restore projection matrix
	glPopMatrix();                   // restore to previous projection matrix

	// restore modelview matrix
	glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
	glPopMatrix();                   // restore to previous modelview matrix
}

void displayCB( void )  {

	glStencilMask(0xffffffff);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);	
	glClearStencil(0x4);
	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(-100, 0, 0);
	glVertex3f(100, 0, 0);
	glColor3f(0, 1, 0);
	glVertex3f(0, -100, 0);
	glVertex3f(0, 100, 0);
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, -100);
	glVertex3f(0, 0, 100);
	glEnd();

	showInfo(mTimer.elapsed());
	GameScene::inst().loop();
	glPopMatrix();
	glutSwapBuffers();
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

void idleCB()
{
	glutPostRedisplay(); //Redraw scene
}

/*
* Callback function for mouse event
*/
void mouseCB(int button, int state, int x, int y) {
	Mouse::inst().processMouse(button, state, x, y);
}

/*
* Callback function for animation motion event
*/
void mouseMotionCB(int x, int y) {
	Mouse::inst().processMouseMotion(x, y);
}

void mousePassiveMotionCB(int x, int y)
{
	Mouse::inst().processMousePassiveMotion(x, y);
}

void keyboardCB(unsigned char key,int x,int y)
{
	printf("Key board %c", key );
	KeyBoard::inst().processKey(key);
}

void timerCB(int value) {
	//GameScene::inst().lightAngle+=0.3;
	glutPostRedisplay(); //Redraw scene
	glutTimerFunc(DELTA_TIME, timerCB, 0); //Call update
}

int main( int argc, char *argv[] )  {
	// init global vars
	initSharedMem();

	// init GLUT and GL
	initGLUT(argc, argv);
	initGL();

	mTimer.start();
	glutMainLoop( );
}



/* ----------------------------------------------------------------------- */

