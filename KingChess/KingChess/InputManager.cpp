#include "InputManager.h"
#include "GameSence.h"
#include "Constants.h"
#include "Camera.h"


KeyBoard::KeyBoard(void)
{
	fullscreen = false;
}

KeyBoard& KeyBoard::inst()
{
	static KeyBoard instance;
	return instance;
}

void KeyBoard::processKey( unsigned char key )
{
	switch(key){
	case 'l':
		Camera::inst().zoom(0.5);
		printf("zoom ++\n");
		break;
	case 's':
		Camera::inst().zoom(-0.5);
		printf("zoom --\n");
	default:
		break;
	}
}

KeyBoard::~KeyBoard(void)
{
}

Mouse::Mouse( void )
{
	mouseLeftDown = mouseRightDown = mouseMiddleDown = false;
	mouseX = mouseY = 0;
}

Mouse& Mouse::inst()
{
	static Mouse instance;
	return instance;
}

void Mouse::processMouse( int button, int state, int x, int y )
{
	if (Graphic::inst().getAppScene() == APP_GAME)
	{
		Camera::inst().save(x, y);

		if(button == GLUT_LEFT_BUTTON)
		{
			if(state == GLUT_DOWN)
				mouseLeftDown = true;
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

		if 	((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
		{
			GameScene::inst().processMouseBegan(x, Graphic::inst().screenHeight-y);
		} 
	}
}

void Mouse::processMouseMotion( int x, int y )
{
	if(mouseRightDown)
	{
		Camera::inst().rotate(x, y);
		GameScene::inst().mAutoCam = false;
	}
}

void Mouse::processMousePassiveMotion( int x, int y )
{
	switch (Graphic::inst().getAppScene())
	{
	case APP_GAME:
		GameScene::inst().processMousePassiveMotion(x, Graphic::inst().screenHeight-y);
		break;
	default:
		break;
	}
}

Mouse::~Mouse( void )
{

}
