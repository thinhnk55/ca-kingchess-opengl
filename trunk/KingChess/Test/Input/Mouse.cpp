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
                
                if(GameScene::inst().mode == MOVING || GameScene::inst().mode == FIGHT || GameScene::inst().mode == END_GAME)
                    return;

                int i = GameScene::inst().getSelectedIndex(x,y);
                std::cout << "Mouse click: " << x << " " << y << " " << i << std::endl;

                
                if(i == -1){ //bam vao mot o trong
                    if(GameScene::inst().prevSelectedCell == NULL || GameScene::inst().currentSelectedCell == NULL)
                        return;

                    int previousindex = GameScene::inst().prevSelectedChestPieceIndex;

                    if(previousindex != -1){
                        if(GameScene::inst().logic->isValidMoving(GameScene::inst().prevSelectedCell,GameScene::inst().currentSelectedCell)){
                            GameScene::inst().mode = MOVING;
                            cout << "Mode: moving" << endl;
                        }
                        else{
                            GameScene::inst().currentSelectedCell = NULL;
                            return;
                        }
             
                    }

                }

                else if(i > -1){//bam vao mot o da co quan co
                     if(GameScene::inst().prevSelectedCell == NULL || GameScene::inst().currentSelectedCell == NULL)
                        return;
                     int previousindex = GameScene::inst().prevSelectedChestPieceIndex;
                     if(previousindex > -1 && GameScene::inst().currentSelectedCell->associatedChessPieceIndex != previousindex){
                         if(GameScene::inst().logic->isValidMoving(GameScene::inst().prevSelectedCell,GameScene::inst().currentSelectedCell)){
                             GameScene::inst().mode = FIGHT;
                             cout << "Mode: fight" << endl;
                         }
                         else{
                             GameScene::inst().currentSelectedCell = NULL;
                             return;
                         }
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

