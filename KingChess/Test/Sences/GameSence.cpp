#include "GameSence.h"
#include "../Entities/LogicGame.h"
#include "../Constant.h"
#include "../Input/Mouse.h"
#include <iostream>
using namespace std;
#define BOARD_Y 28
GameScene::GameScene(void)
{
	logic = new LogicGame();
	yCir = -15;

	lightPosition[0] = 150;
	lightPosition[1] = 150;
    lightPosition[2] = 0;
	lightPosition[3] = 1;
	//lightAngle = 90.0;

	//lightHeight = 0;

	initEnties();

    prevSelectedChestPieceIndex = -1;
    currentSelectedCell = NULL;
    prevSelectedCell = NULL;
    t = 0;
    mode = IDLE;
    cout << "Turn: " << logic->turn << endl;
    //light = new Light();
}

GameScene& GameScene::inst()
{
	static GameScene Instance;
	return Instance;
}
void GameScene::initBoardCells(){
	cell = new ExtraModel();
	cell->loadModel("Models/cell.obj");
    cell->mVisible = false;
    int modelIndex = 0;
    //hang thu 0
    for(int x = 0 ; x < BOARD_SIZE ; x++){
        allCells[x][0] = new ExtraModel(cell);
        if(x == 0){
            allCells[x][0]->setPosition(Vector3(-44, 2 + BOARD_Y, 44));
        }
        else{
            float posX,posY,posZ;

            if(x % 2 != 0)
                allCells[x][0]->setPosition(Vector3(allCells[x-1][0]->getPosition().x + 13 , 2+ BOARD_Y, 44));
            else 
                allCells[x][0]->setPosition(Vector3(allCells[x-1][0]->getPosition().x + 12, 2+ BOARD_Y, 44));
        }
        allCells[x][0]->boardIndexX = x;
        allCells[x][0]->boardIndexY = 0;
        allCells[x][0]->associatedChessPieceIndex = modelIndex;
        modelIndex++;
    }

    //hang thu 1
    for(int x = 0 ; x < BOARD_SIZE ; x++){
        allCells[x][1] = new ExtraModel(cell);
        if(x == 0){
            allCells[x][1]->setPosition(Vector3(-44, 2+ BOARD_Y, 31));
        }
        else{
            float posX,posY,posZ;
            if(x % 2 != 0)
                allCells[x][1]->setPosition(Vector3(allCells[x-1][1]->getPosition().x + 13, 2+ BOARD_Y, 31));
            else 
                allCells[x][1]->setPosition(Vector3(allCells[x-1][1]->getPosition().x + 12, 2+ BOARD_Y, 31));
        }
        allCells[x][1]->boardIndexX = x;
        allCells[x][1]->boardIndexY = 1;
        allCells[x][1]->associatedChessPieceIndex = modelIndex;
        modelIndex++;
    }

     //hang thu 2
    for(int x = 0 ; x < BOARD_SIZE ; x++){
        allCells[x][2] = new ExtraModel(cell);
        if(x == 0){
            allCells[x][2]->setPosition(Vector3(-44, 2+ BOARD_Y, 19));
        }
        else{
            float posX,posY,posZ;

            //cout << posX << posY << posZ << endl;
            if(x % 2 != 0)
                allCells[x][2]->setPosition(Vector3(allCells[x-1][2]->getPosition().x + 13, 2+ BOARD_Y, 19));
            else 
                allCells[x][2]->setPosition(Vector3(allCells[x-1][2]->getPosition().x + 12, 2+ BOARD_Y, 19));
        }
        allCells[x][2]->boardIndexX = x;
        allCells[x][2]->boardIndexY = 2;
    }

     //hang thu 3
    for(int x = 0 ; x < BOARD_SIZE ; x++){
        allCells[x][3] = new ExtraModel(cell);
        if(x == 0){
            allCells[x][3]->setPosition(Vector3(-44, 2+ BOARD_Y, 6));
        }
        else{
            float posX,posY,posZ;

            //cout << posX << posY << posZ << endl;
            if(x % 2 != 0)
                allCells[x][3]->setPosition(Vector3(allCells[x-1][3]->getPosition().x + 13, 2+ BOARD_Y, 6));
            else 
                allCells[x][3]->setPosition(Vector3(allCells[x-1][3]->getPosition().x + 12, 2+ BOARD_Y, 6));
        }
        allCells[x][3]->boardIndexX = x;
        allCells[x][3]->boardIndexY = 3;
    }

     //hang thu 4
    for(int x = 0 ; x < BOARD_SIZE ; x++){
        allCells[x][4] = new ExtraModel(cell);
        if(x == 0){
            allCells[x][4]->setPosition(Vector3(-44, 2+ BOARD_Y, -6));
        }
        else{
            float posX,posY,posZ;

            //cout << posX << posY << posZ << endl;
            if(x % 2 != 0)
                allCells[x][4]->setPosition(Vector3(allCells[x-1][4]->getPosition().x + 13, 2+ BOARD_Y, -6));
            else 
                allCells[x][4]->setPosition(Vector3(allCells[x-1][4]->getPosition().x + 12, 2+ BOARD_Y, -6));
        }
        allCells[x][4]->boardIndexX = x;
        allCells[x][4]->boardIndexY = 4;
    }

     //hang thu 5
    for(int x = 0 ; x < BOARD_SIZE ; x++){
        allCells[x][5] = new ExtraModel(cell);
        if(x == 0){
            allCells[x][5]->setPosition(Vector3(-44, 2+ BOARD_Y, -19));
        }
        else{
            float posX,posY,posZ;

            //cout << posX << posY << posZ << endl;
            if(x % 2 != 0)
                allCells[x][5]->setPosition(Vector3(allCells[x-1][5]->getPosition().x + 13, 2+ BOARD_Y, -19));
            else 
                allCells[x][5]->setPosition(Vector3(allCells[x-1][5]->getPosition().x + 12, 2+ BOARD_Y, -19));
        }
        allCells[x][5]->boardIndexX = x;
        allCells[x][5]->boardIndexY = 5;
    }

     //hang thu 6
    for(int x = 0 ; x < BOARD_SIZE ; x++){
        allCells[x][6] = new ExtraModel(cell);
        if(x == 0){
            allCells[x][6]->setPosition(Vector3(-44, 2+ BOARD_Y, -31));
        }
        else{
            float posX,posY,posZ;

            //cout << posX << posY << posZ << endl;
            if(x % 2 != 0)
                allCells[x][6]->setPosition(Vector3(allCells[x-1][6]->getPosition().x + 13, 2+ BOARD_Y, -31));
            else 
                allCells[x][6]->setPosition(Vector3(allCells[x-1][6]->getPosition().x + 12, 2+ BOARD_Y, -31));
        }
        allCells[x][6]->boardIndexX = x;
        allCells[x][6]->boardIndexY = 6;
        allCells[x][6]->associatedChessPieceIndex = modelIndex;
        modelIndex++;
    }

     //hang thu 7
    for(int x = 0 ; x < BOARD_SIZE ; x++){
        allCells[x][7] = new ExtraModel(cell);
        if(x == 0){
            allCells[x][7]->setPosition(Vector3(-44, 2+ BOARD_Y, -44));
        }
        else{
            float posX,posY,posZ;

            //cout << posX << posY << posZ << endl;
            if(x % 2 != 0)
                allCells[x][7]->setPosition(Vector3(allCells[x-1][7]->getPosition().x + 13, 2+ BOARD_Y, -44));
            else 
                allCells[x][7]->setPosition(Vector3(allCells[x-1][7]->getPosition().x + 12, 2+ BOARD_Y, -44));
        }
        allCells[x][7]->boardIndexX = x;
        allCells[x][7]->boardIndexY = 7;
        allCells[x][7]->associatedChessPieceIndex = modelIndex;
        modelIndex++;
    }

    for(int i = 0 ; i < BOARD_SIZE ; i++){
        for(int j = 0 ; j < BOARD_SIZE ; j++){
            cout << allCells[j][i]->associatedChessPieceIndex << " ";
        }
        cout << endl;
    }
}

void GameScene::initChessPiecesModels(){
    pawnRedTempModel = new BaseModel();
	pawnRedTempModel->loadModel("Models/pawn.obj");
	pawnRedTempModel->setPosition(Vector3(0, 8, 0));
	pawnRedTempModel->setAngleRotate(90.0);
	pawnRedTempModel->mVisible = true;
    printf("model Pos = (%f, %f, %f)\n", pawnRedTempModel->getPosition().x, pawnRedTempModel->getPosition().y, pawnRedTempModel->getPosition().z);
	printf("model Anchor point = (%f, %f, %f)\n", pawnRedTempModel->getAnchorPoint().x, pawnRedTempModel->getAnchorPoint().y, pawnRedTempModel->getAnchorPoint().z);
    
    //set red pawns positions
    models[PAWN_RED_1] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_1]->setPosition(Vector3(-44,7 + BOARD_Y,31));
    models[PAWN_RED_2] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_2]->setPosition(Vector3(-31,7  + BOARD_Y,31));
    models[PAWN_RED_3] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_3]->setPosition(Vector3(-19,7  + BOARD_Y,31));
    models[PAWN_RED_4] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_4]->setPosition(Vector3(-6,7 + BOARD_Y,31));
    models[PAWN_RED_5] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_5]->setPosition(Vector3(6,7 + BOARD_Y,31));
    models[PAWN_RED_6] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_6]->setPosition(Vector3(19,7 + BOARD_Y,31));
    models[PAWN_RED_7] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_7]->setPosition(Vector3(31, 7+ BOARD_Y,31));
    models[PAWN_RED_8] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_8]->setPosition(Vector3(44,7 + BOARD_Y,31));

    //set red bishops positions
    models[BISHOP_RED_1] = new BaseModel();
    models[BISHOP_RED_1]->loadModel("Models/Bishop.obj");
    models[BISHOP_RED_1]->setPosition(Vector3(-19,9+ BOARD_Y,44));
    models[BISHOP_RED_2] = new BaseModel(models[BISHOP_RED_1]);
    models[BISHOP_RED_2]->setPosition(Vector3(19,9+ BOARD_Y,44));

    //set red knights positions
    models[KNIGHT_RED_1] = new BaseModel();
    models[KNIGHT_RED_1]->loadModel("Models/knight.obj");
    models[KNIGHT_RED_1]->setPosition(Vector3(-32,9+ BOARD_Y,44));
    models[KNIGHT_RED_1]->setAngleRotate(-90);
    models[KNIGHT_RED_2] = new BaseModel(models[KNIGHT_RED_1]);
    models[KNIGHT_RED_2]->setPosition(Vector3(32,9+ BOARD_Y,44));

    //set red rooks positions
    models[ROOK_RED_1] = new BaseModel();
    models[ROOK_RED_1]->loadModel("Models/Rook.obj");
    models[ROOK_RED_1]->setPosition(Vector3(-44,9+ BOARD_Y,44));
    models[ROOK_RED_2] = new BaseModel(models[ROOK_RED_1]);
    models[ROOK_RED_2]->setPosition(Vector3(44,9+ BOARD_Y,44));

    //set red queen positions
    models[QUEEN_RED] = new BaseModel();
    models[QUEEN_RED]->loadModel("Models/Queen.obj");
    models[QUEEN_RED]->setPosition(Vector3(-6,9+ BOARD_Y,44));

    //set red king positions
    models[KING_RED] = new BaseModel();
    models[KING_RED]->loadModel("Models/King.obj");
    models[KING_RED]->setPosition(Vector3(6,10+ BOARD_Y,44));

    //set blue pawns positions
    models[PAWN_BLUE_1] = new BaseModel();
    models[PAWN_BLUE_1]->loadModel("Models/PawnBlue.obj");
    models[PAWN_BLUE_1]->setPosition(Vector3(-44,7+ BOARD_Y,-31));
    models[PAWN_BLUE_2] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_2]->setPosition(Vector3(-31,7+ BOARD_Y,-31));
    models[PAWN_BLUE_3] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_3]->setPosition(Vector3(-19,7+ BOARD_Y,-31));
    models[PAWN_BLUE_4] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_4]->setPosition(Vector3(-6,7+ BOARD_Y,-31));
    models[PAWN_BLUE_5] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_5]->setPosition(Vector3(6,7+ BOARD_Y,-31));
    models[PAWN_BLUE_6] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_6]->setPosition(Vector3(19,7+ BOARD_Y,-31));
    models[PAWN_BLUE_7] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_7]->setPosition(Vector3(31,7+ BOARD_Y,-31));
    models[PAWN_BLUE_8] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_8]->setPosition(Vector3(44,7+ BOARD_Y,-31));

    //set blue rooks positions
    models[ROOK_BLUE_1] = new BaseModel();
    models[ROOK_BLUE_1]->loadModel("Models/RookBlue.obj");
    models[ROOK_BLUE_1]->setPosition(Vector3(-44,9+ BOARD_Y,-44));
    models[ROOK_BLUE_2] = new BaseModel(models[ROOK_BLUE_1]);
    models[ROOK_BLUE_2]->setPosition(Vector3(44,9+ BOARD_Y,-44));

    //set blue knights positions
    models[KNIGHT_BLUE_1] = new BaseModel();
    models[KNIGHT_BLUE_1]->loadModel("Models/knightBlue.obj");
    models[KNIGHT_BLUE_1]->setPosition(Vector3(-32,9+ BOARD_Y,-44));
    models[KNIGHT_BLUE_1]->setAngleRotate(90);
    models[KNIGHT_BLUE_2] = new BaseModel(models[KNIGHT_BLUE_1]);
    models[KNIGHT_BLUE_2]->setPosition(Vector3(32,9+ BOARD_Y,-44));

    //set blue bishops positions
    models[BISHOP_BLUE_1] = new BaseModel();
    models[BISHOP_BLUE_1]->loadModel("Models/BishopBlue.obj");
    models[BISHOP_BLUE_1]->setPosition(Vector3(-19,9+ BOARD_Y,-44));
    models[BISHOP_BLUE_2] = new BaseModel(models[BISHOP_BLUE_1]);
    models[BISHOP_BLUE_2]->setPosition(Vector3(19,9+ BOARD_Y,-44));

    //set blue queen positions
    models[QUEEN_BLUE] = new BaseModel();
    models[QUEEN_BLUE]->loadModel("Models/QueenBlue.obj");
    models[QUEEN_BLUE]->setPosition(Vector3(-6,9+ BOARD_Y,-44));

    //set blue king positions
    models[KING_BLUE] = new BaseModel();
    models[KING_BLUE]->loadModel("Models/KingBlue.obj");
    models[KING_BLUE]->setPosition(Vector3(6,10+ BOARD_Y,-44));
}
void GameScene::initEnties(){
	printf("Load OBJ start \n");
	
	board = new BaseModel();
	board->loadModel("Models/Board.obj");
	board->setPosition(Vector3(0, 28, 0));

    initChessPiecesModels();
	initBoardCells();
	
	//initSky();
	initGround();

	

	printf("==========END============");
}

void GameScene::initSky(){
	sky         = new ExtraModel();
	sky->loadModel("Models/sky.obj");
}
void GameScene::initGround(){
	ground = new ExtraModel();
	ground->loadModel("Models/ground.obj");
	ground->setPosition(Vector3(0, -2, 0));
    table = new ExtraModel();
    table->loadModel("Models/table.obj");
    table->setPosition(Vector3(0,10,0));
}
void GameScene::loop()
{
    Vector3 P;
    if(mode == MOVING){
        if(t <= 1){//moving

            P = tween(models[prevSelectedChestPieceIndex]->getPosition(),currentSelectedCell->getPosition(),t);

            models[prevSelectedChestPieceIndex]->setPosition(P);

            drawSence();

            t += 0.1;

            Sleep(100);

        }
        else{

            t = 0;
            mode = IDLE;

            logic->transformPawnToQueen(prevSelectedCell,currentSelectedCell,prevSelectedChestPieceIndex);

            currentSelectedCell->associatedChessPieceIndex = prevSelectedChestPieceIndex;
            prevSelectedCell->associatedChessPieceIndex = -1;

            /*reset marked cell*/
            prevSelectedCell = NULL;
            currentSelectedCell = NULL;
            models[prevSelectedChestPieceIndex]->mDrawKnife = false;
            prevSelectedChestPieceIndex = -1;

            for(int i = 0 ; i < BOARD_SIZE ; i++){
                for(int j = 0 ; j < BOARD_SIZE ; j++){
                    cout << allCells[j][i]->associatedChessPieceIndex << " ";
                }
                cout << endl;
            }

            /*change turn*/
            logic->changeTurn();
            drawSence();
        }
    }

    else if( mode == IDLE){
	    drawSence();
        
    }
    else if (mode == FIGHT){
        //fight here
        if(t <= 1){//moving

            P = tween(models[prevSelectedChestPieceIndex]->getPosition(),currentSelectedCell->getPosition(),t);

            models[prevSelectedChestPieceIndex]->setPosition(P);

            drawSence();

            t += 0.1;

            Sleep(100);

        }
        else{

            moveChestPieceOutTheBoard(currentSelectedCell);
            //logic->changeTurn();
            drawSence();
        }
    }

    else if(mode == END_GAME){
        drawSence();
    }
}

void GameScene::drawCells(){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			if(allCells[i][j]!= NULL && allCells[i][j]->mVisible){
				allCells[i][j]->drawModel();
			}
		}
	}
}

void GameScene::drawSence(){

	//float _ambient[4] = {1, 1, 1, 1};
	//glLightfv(GL_LIGHT0, GL_AMBIENT,  _ambient);

	//sky->drawModel();
	
	//light->setAmbient();

	drawCells();
	ground->drawModel();
    table->drawModel();
	board->drawModel();
	//pawnRedTempModel->drawModel();

    for(int i = 0 ; i < 32 ; i++){
        if(models[i] != NULL)
            models[i] ->drawModel();
    }
	

	//Debug light
	Light::inst().setPosition(lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
	Light::inst().drawLightSource(lightAngle, lightHeight);

	//Debug ray
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);

	Vector3 a = mViewRay.origin + 200*mViewRay.direction;
	glVertex3f(mViewRay.origin.x, mViewRay.origin.y, mViewRay.origin.z);
	glVertex3f(a.x, a.y, a.z);
    //cout << mViewRay.origin.x << " " << mViewRay.origin.y << " " << mViewRay.origin.z << endl;
       
	glEnd();
	glEnable(GL_LIGHTING);  
}


void GameScene::processMouseBegan( int x, int y )
{
	
}

void GameScene::processMousePassiveMotion( int x, int y )
{

}

void GameScene::processMouseEnded(int x, int y){

}

void GameScene::processKeyBoard(unsigned key, int x, int y){
	switch (key)
	{
	case 'x':
		pawnRedTempModel->moveDown(1);
		printf("model Pos = (%f, %f, %f)\n", pawnRedTempModel->getPosition().x, pawnRedTempModel->getPosition().y, pawnRedTempModel->getPosition().z);
		printf("model Anchor point = (%f, %f, %f)\n", pawnRedTempModel->getAnchorPoint().x, pawnRedTempModel->getAnchorPoint().y, pawnRedTempModel->getAnchorPoint().z);
		break;

	case 'z':
		pawnRedTempModel->moveUp(1);
		printf("pawnRedTemppawnRedTempModel Pos = (%f, %f, %f)\n", pawnRedTempModel->getPosition().x, pawnRedTempModel->getPosition().y, pawnRedTempModel->getPosition().z);
		printf("pawnRedTempModel Anchor point = (%f, %f, %f)\n", pawnRedTempModel->getAnchorPoint().x, pawnRedTempModel->getAnchorPoint().y, pawnRedTempModel->getAnchorPoint().z);
		break;

	case 'a':
		pawnRedTempModel->moveLeft(1);
		printf("pawnRedTempModel Pos = (%f, %f, %f)\n", pawnRedTempModel->getPosition().x, pawnRedTempModel->getPosition().y, pawnRedTempModel->getPosition().z);
		printf("pawnRedTempModel Anchor point = (%f, %f, %f)\n", pawnRedTempModel->getAnchorPoint().x, pawnRedTempModel->getAnchorPoint().y, pawnRedTempModel->getAnchorPoint().z);
		break;

	case 'd':
		pawnRedTempModel->moveRight(1);
		printf("pawnRedTempModel Pos = (%f, %f, %f)\n", pawnRedTempModel->getPosition().x, pawnRedTempModel->getPosition().y, pawnRedTempModel->getPosition().z);
		printf("pawnRedTempModel Anchor point = (%f, %f, %f)\n", pawnRedTempModel->getAnchorPoint().x, pawnRedTempModel->getAnchorPoint().y, pawnRedTempModel->getAnchorPoint().z);
		break;
	case 'w':
		pawnRedTempModel->moveIn(1);
		printf("pawnRedTempModel Pos = (%f, %f, %f)\n", pawnRedTempModel->getPosition().x, pawnRedTempModel->getPosition().y, pawnRedTempModel->getPosition().z);
		printf("pawnRedTempModel Anchor point = (%f, %f, %f)\n", pawnRedTempModel->getAnchorPoint().x, pawnRedTempModel->getAnchorPoint().y, pawnRedTempModel->getAnchorPoint().z);
		break;
	case 's':
		pawnRedTempModel->moveOut(1);
		printf("pawnRedTempModel Pos = (%f, %f, %f)\n", pawnRedTempModel->getPosition().x, pawnRedTempModel->getPosition().y, pawnRedTempModel->getPosition().z);
		printf("pawnRedTempModel Anchor point = (%f, %f, %f)\n", pawnRedTempModel->getAnchorPoint().x, pawnRedTempModel->getAnchorPoint().y, pawnRedTempModel->getAnchorPoint().z);
		break;
	}
}

int GameScene::getSelectedIndex(int mousex, int mousey){

    float minDist = -1;
    float currentDist = -1;
    // Get x, y coordinate in zNear plane
	int window_y = (Graphic::inst().screenHeight - mousey) - Graphic::inst().screenHeight/2;
	double norm_y = double(window_y)/double(Graphic::inst().screenHeight/2);
	int window_x = mousex - Graphic::inst().screenWidth/2;
	double norm_x = double(window_x)/double(Graphic::inst().screenWidth/2);

	float aspect = Graphic::inst().screenWidth/Graphic::inst().screenHeight;

	float y = Graphic::inst().near_height * norm_y;
	float x = Graphic::inst().near_height * aspect * norm_x;

    // Get ModelView matrix
	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX , m);

	Matrix4 inverseModelViewMatrix = Matrix4(m).inverse();

    Vector4 origin = Vector4()*inverseModelViewMatrix;
    Vector3 direction = Vector3(x,y,-Graphic::inst().zNear)*inverseModelViewMatrix;

    cout << origin.toString() << endl;

    mViewRay.set(origin.toVector3(),direction);

    int index = -1;

    bool found = false;
    int i,j;
    if(mode != END_GAME){
        for(i = 0 ; i < BOARD_SIZE ; i++){
            for(j  = 0 ; j < BOARD_SIZE ; j++){
                if(mViewRay.hasIntersected(allCells[j][i]->boundingbox())){
                    cout << "Selected cell: " << j << "-" << i << endl;
                    found = true;
                    index = allCells[j][i]->associatedChessPieceIndex;
                    //currentSelectedCell = allCells[j][i];
                    break;
                }
            }
            if(found) break;
        }
        /*nếu là turn red thì chỉ cho phép chọn quân 0->15*/
        if(logic->turn == Turn::RED){
            if(index >= 0 && index <= 15){
                if(prevSelectedCell == NULL){
                    prevSelectedCell = allCells[j][i];
                    prevSelectedChestPieceIndex = index;
                    models[index]->mDrawKnife = true;
                }

                else if(prevSelectedCell != NULL){

                    if(index >= 0 && index <= 15){//bam vao o thu 2 cung quan red thi chuyen select sang quan nay
                        models[prevSelectedChestPieceIndex]->mDrawKnife = false;
                        prevSelectedCell = allCells[j][i];
                        prevSelectedChestPieceIndex = index;
                        models[index]->mDrawKnife = true;
                    }
                    
                    else
                        currentSelectedCell = allCells[j][i];
                }
                
            }

            else 
            {
                if(prevSelectedCell != NULL)
                    currentSelectedCell = allCells[j][i];
            }

            if(!found) return -2; //ko bam vao o nao
            else return index;
        }

        /*turn blue chọn quân 16->31 */
        else if(logic->turn == Turn::BLUE){
            if(index >= 16 && index <= 31){
                if(prevSelectedCell == NULL){
                    prevSelectedCell = allCells[j][i];
                    prevSelectedChestPieceIndex = index;
                    models[index]->mDrawKnife = true;
                }

                else if(prevSelectedCell != NULL){

                    if(index >= 16 && index <= 31){//bam vao o thu 2 cung quan blue thi chuyen select sang quan nay
                        models[prevSelectedChestPieceIndex]->mDrawKnife = false;
                        prevSelectedCell = allCells[j][i];
                        prevSelectedChestPieceIndex = index;
                        models[index]->mDrawKnife = true;
                    }
                    
                    else
                        currentSelectedCell = allCells[j][i];
                }
            }

            else 
            {
                if(prevSelectedCell != NULL)
                    currentSelectedCell = allCells[j][i];
            }

            if(!found) return -2; //ko bam vao o nao
            else return index;
        }
    }
    
}

GameScene::~GameScene(void)
{

}

Vector3 GameScene::tween(Vector3 A, Vector3 B, float t){
    Vector3 result;
    result.x = A.x*(1 - t) + B.x*t;
    result.z = A.z*(1 - t) + B.z*t;
    result.y = A.y;
    return result;
}

void GameScene::moveChestPieceOutTheBoard(ExtraModel* boardcell){
    Vector3 B(-62,boardcell->getPosition().y ,boardcell->getPosition().z);
    Vector3 A(models[boardcell->associatedChessPieceIndex]->getPosition().x,models[boardcell->associatedChessPieceIndex]->getPosition().y - 0.65,models[boardcell->associatedChessPieceIndex]->getPosition().z);
    Vector3 P;
    if(boardcell->associatedChessPieceIndex < 16){//quan red thi move sang ben trai
        
        if(t <= 2){
            P = tween(A, B, t - 1);
            models[boardcell->associatedChessPieceIndex]->setPosition(P);
            drawSence();
            t += 0.1;
            Sleep(100);
        }
        else{
            t = 0;

            if(boardcell->associatedChessPieceIndex == KING_RED){
                cout << "End game!" << endl << "Winner: White" << endl;
                mode = END_GAME;
                drawSence();
                return;
            }

            mode = IDLE;
            logic->transformPawnToQueen(prevSelectedCell,currentSelectedCell,prevSelectedChestPieceIndex);

            currentSelectedCell->associatedChessPieceIndex = prevSelectedChestPieceIndex;
            prevSelectedCell->associatedChessPieceIndex = -1;
            
            /*reset marked cell*/
            prevSelectedCell = NULL;
            currentSelectedCell = NULL;
            models[prevSelectedChestPieceIndex]->mDrawKnife = false;
            prevSelectedChestPieceIndex = -1;
            for(int i = 0 ; i < BOARD_SIZE ; i++){
                for(int j = 0 ; j < BOARD_SIZE ; j++){
                    cout << allCells[j][i]->associatedChessPieceIndex << " ";
                }
                cout << endl;
            }
            logic->changeTurn();
            drawSence();
        }
    }
    else {//quan blue thi move sang ben phai
        B.set(62,boardcell->getPosition().y ,boardcell->getPosition().z);
        if(t <= 2){
            P = tween(A, B, t - 1);
            models[boardcell->associatedChessPieceIndex]->setPosition(P);
            drawSence();
            t += 0.1;
            Sleep(100);
        }
        else{
            t = 0;
            if(boardcell->associatedChessPieceIndex == KING_BLUE){
                cout << "End game!" << endl << "Winner: Black" << endl;
                mode = END_GAME;
                drawSence();
                return;
            }
            mode = IDLE;
            logic->transformPawnToQueen(prevSelectedCell,currentSelectedCell,prevSelectedChestPieceIndex);

            currentSelectedCell->associatedChessPieceIndex = prevSelectedChestPieceIndex;
            prevSelectedCell->associatedChessPieceIndex = -1;
            
            /*reset marked cell*/
            prevSelectedCell = NULL;
            currentSelectedCell = NULL;
            models[prevSelectedChestPieceIndex]->mDrawKnife = false;
            prevSelectedChestPieceIndex = -1;
            for(int i = 0 ; i < BOARD_SIZE ; i++){
                for(int j = 0 ; j < BOARD_SIZE ; j++){
                    cout << allCells[j][i]->associatedChessPieceIndex << " ";
                }
                cout << endl;
            }
            logic->changeTurn();
            drawSence();
        }
    }
}
