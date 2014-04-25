#include "Mouse.h"
#include <GL/freeglut.h>
#include "../Control/Camera.h"
#include <iostream>

Mouse::Mouse( void )
{
	mouseLeftDown = mouseRightDown = mouseMiddleDown = false;
	mouseX = mouseY = -1;
}

Mouse& Mouse::inst()
{
	static Mouse instance;
	return instance;
}

void Mouse::processMouse( int button, int state, int x, int y )
{
	Camera::inst().save(x, y);	
	if(button == GLUT_LEFT_BUTTON)
		{
			if(state == GLUT_DOWN){
                
				mouseLeftDown = true;
                int i = GameScene::inst().getSelectedIndex(x,y);
                std::cout << "Mouse click: " << x << " " << y << " " << i << std::endl;

            }
			else if(state == GLUT_UP)
				mouseLeftDown = false;
		}

	else if(button == GLUT_RIGHT_BUTTON)
		{
			if(state == GLUT_DOWN)

				mouseRightDown = true;		
			else if(state == GLUT_UP)
				mouseRightDown = false;
		}

	else if(button == GLUT_MIDDLE_BUTTON)
		{
			if(state == GLUT_DOWN)
				mouseMiddleDown = true;
			else if(state == GLUT_UP)
				mouseMiddleDown = false;
		}
}

void Mouse::processMouseMotion( int x, int y )
{
	if(mouseRightDown)
	{
		Camera::inst().rotate(x, y);		
	}

}

void Mouse::processMousePassiveMotion( int x, int y )
{
	
}

Mouse::~Mouse( void )
{

}
