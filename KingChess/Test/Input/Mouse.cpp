#include "Mouse.h"
#include <GL/freeglut.h>
#include "../Control/Camera.h"
#include <iostream>
#include <Windows.h>
#include "../Constant.h"
using namespace std;

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
                
                if(GameScene::inst().mode == MOVING)
                    return;

                int i = GameScene::inst().getSelectedIndex(x,y);
                std::cout << "Mouse click: " << x << " " << y << " " << i << std::endl;

                
                if(i == -1){ //bam vao mot o trong
                    if(GameScene::inst().prevSelectedCell == NULL || GameScene::inst().currentSelectedCell == NULL)
                        return;

                    int previousindex = GameScene::inst().prevSelectedChestPieceIndex;
                    if(previousindex != -1){
                        
                        GameScene::inst().mode = MOVING;
                        cout << "Mode: moving" << endl;
                        //cout << "A: " << A.x << A.y << A.z << endl;
                        //cout << "B: " << B.x << B.y << B.z << endl;
                        //cout << "P: " << P.x << P.y << P.z << endl;
                        //then set the board cell to associate with none chest piece
                        
                    }
                }

                else if(i > -1){//bam vao mot o da co quan co
                     if(GameScene::inst().prevSelectedCell == NULL || GameScene::inst().currentSelectedCell == NULL)
                        return;
                     int previousindex = GameScene::inst().prevSelectedChestPieceIndex;
                     if(previousindex > -1 && GameScene::inst().currentSelectedCell->associatedChessPieceIndex != previousindex){
                         GameScene::inst().mode = FIGHT;
                         cout << "Mode: fight" << endl;
                     }   
                }

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

