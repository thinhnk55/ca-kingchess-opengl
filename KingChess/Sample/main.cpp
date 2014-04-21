#include <GL/freeglut.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include "Light.h"
#include "Graphic.h"
#include "Camera.h"
float angle = 0;

GLuint texture[40];

void freetexture (GLuint texture) {
	glDeleteTextures( 1, &texture );
}

GLuint loadtextures (const char *filename, float width, float 
			  height) {
				  GLuint texture;

				  unsigned char *data;
				  FILE *file;

				  file = fopen( filename, "rb" );
				  if ( file == NULL ) return 0;

				  data = (unsigned char *)malloc( width * height * 3 );
				  fread( data, width * height * 3, 1, file );

				  fclose( file );

				  glGenTextures( 1, &texture );
				  glBindTexture( GL_TEXTURE_2D, texture );
				  glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, 
					  GL_MODULATE );
				  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
					  GL_LINEAR_MIPMAP_NEAREST );
				  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
					  GL_LINEAR );
				  gluBuild2DMipmaps( GL_TEXTURE_2D, 3, width, height, 
					  GL_RGB, GL_UNSIGNED_BYTE, data );

				  data = NULL;

				  return texture;
}

void square (void) {
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,texture[0]);
	glTranslatef(0,2.5,0);
	glScalef(2,2,2);
	glBegin(GL_QUADS);
	glTexCoord2f(1,0);
	glVertex3f(-1,-1,0);
	glTexCoord2f(1,1);
	glVertex3f(-1,1,0);
	glTexCoord2f(0,1);
	glVertex3f(1,1,0);
	glTexCoord2f(0,0);
	glVertex3f(1,-1,0);
	glEnd();
	glPopMatrix();
}

void bench (void) {
	glPushMatrix();
	glColor4f(1,1,1,0.7);
	glBindTexture(GL_TEXTURE_2D,texture[1]);
	glTranslatef(0,-2.5,0);
	glScalef(4,2,4);
	glBegin(GL_QUADS);
	glTexCoord2f(1,0);
	glVertex3f(-1,-1,1);
	glTexCoord2f(1,1);
	glVertex3f(-1,1,-0.5);
	glTexCoord2f(0,1);
	glVertex3f(1,1,-0.5);
	glTexCoord2f(0,0);
	glVertex3f(1,-1,1);
	glEnd();
	glPopMatrix();
}

void display (void) {
	glClearStencil(0); //clear the stencil buffer
	glClearDepth(1.0f);
	glClearColor (1.0,1.0,1.0,1);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | 
		GL_STENCIL_BUFFER_BIT); //clear the buffers
	glLoadIdentity();

	glTranslatef(0, 0, -10);

	//start
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE); //disable the color mask
	glDepthMask(GL_FALSE); //disable the depth mask

	glEnable(GL_STENCIL_TEST); //enable the stencil testing

	glStencilFunc(GL_ALWAYS, 1, 0xFFFFFFFF);
	glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE); //set	the stencil buffer to replace our next lot of data

	bench(); //set the data plane to be replaced

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE); //enable	the color mask
	glDepthMask(GL_TRUE); //enable the depth mask

	glStencilFunc(GL_EQUAL, 1, 0xFFFFFFFF);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP); //set the stencil	buffer to keep our next lot of data

	glDisable(GL_TEXTURE_2D); //disable texturing of the 	shadow
	glDisable(GL_DEPTH_TEST); //disable depth testing of the	shadow
	glPushMatrix();
	glScalef(1.0f, -1.0f, 1.0f); //flip the shadow vertically

	glTranslatef(0,2,0); //translate the shadow onto our 	drawing plane
	

	glColor4f(0.3,0.3,0.3,0.3); //color the shadow black
	square(); //draw our square as the shadow
	glPopMatrix();
	glEnable(GL_DEPTH_TEST); //enable depth testing
	glEnable(GL_TEXTURE_2D); //enable texturing
	glDisable(GL_STENCIL_TEST); //disable the stencil testing

	//end

	glEnable(GL_BLEND); //enable alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //set teh alpha blending

	bench(); //draw our bench

	glDisable(GL_BLEND); //disable alpha blending

	square(); //draw the square

	glutSwapBuffers();
}

void init (void) {
	float lightPosition[4];
	lightPosition[0] = 0;
	lightPosition[1] = 25;
	lightPosition[2] = 0;
	lightPosition[3] = 0;
	//float lightAngle = 60.0;
	//float lightHeight = 25;

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);    
	glShadeModel (GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_TEXTURE_2D);

	//Lighting
	Light::inst().setPosition(lightPosition[0], lightPosition[1], 
		lightPosition[2], lightPosition[3]);

	texture[0] = loadtextures("grass.jpg", 256,256);
	texture[1] = loadtextures("sky.jpg", 256,256);

	Graphic::inst().screenWidth = 500;
	Graphic::inst().screenHeight = 500;

	float aspect = double(500)/double(500);

	// set viewport to be the entire window
	glViewport(0, 0, 500, 500);

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

void reshape (int w, int h) {
	glViewport (0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 1000.0
		);
	glMatrixMode (GL_MODELVIEW);
}

int main (int argc, char **argv) {
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_STENCIL); //add a stencil buffer to the window
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("A basic OpenGL Window");
	init();
	glutDisplayFunc (display);
	glutIdleFunc (display);
	glutReshapeFunc (reshape);
	glutMainLoop ();
	return 0;
}