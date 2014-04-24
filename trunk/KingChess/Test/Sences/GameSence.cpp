#include "GameSence.h"
#include "../Entities/LogicGame.h"
#include "../Constant.h"



GameScene::GameScene(void)
{
	logic = new LogicGame();
	yCir = -15;
	lightPosition[0] = 0;
	lightPosition[1] = 20;
	lightPosition[2] = 0;
	lightPosition[3] = 1;
	lightAngle = 0.0;
	lightHeight = 20;

	initEnties();

    prevSelected = -1;
}

GameScene& GameScene::inst()
{
	static GameScene Instance;
	return Instance;
}
void GameScene::initSprites(){
	cell = new ExtraModel();
	cell->loadModel("Models/cell.obj");
	
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			allCells[i][j] = new ExtraModel(cell);
			allCells[i][j]->setPosition(Vector3(2, 0, 2));
		}
	}
}
void GameScene::initEnties(){
	printf("Load OBJ start \n");
	pawnRedTempModel = new BaseModel();
	pawnRedTempModel->loadModel("Models/pawn.obj");
	pawnRedTempModel->setPosition(Vector3(0, 8, 0));
	pawnRedTempModel->setAngleRotate(90.0);
	//pawnRedTempModel->mShadow = true;
	//pawnRedTempModel->mSelected = true;
	//pawnRedTempModel->mDrawKnife = true;
	//pawnRedTempModel->mDrawShield = true;
	pawnRedTempModel->mVisible = true;
    
	printf("model Pos = (%f, %f, %f)\n", pawnRedTempModel->getPosition().x, pawnRedTempModel->getPosition().y, pawnRedTempModel->getPosition().z);
	printf("model Anchor point = (%f, %f, %f)\n", pawnRedTempModel->getAnchorPoint().x, pawnRedTempModel->getAnchorPoint().y, pawnRedTempModel->getAnchorPoint().z);

	board = new BaseModel();
	board->loadModel("Models/Board.obj");
	board->setPosition(Vector3(0, 0, 0));
	board->mShadow = false;
	board->mSelected = false;
	printf("Finish objects\n");

	initSprites();
	
	//initSky();

	printf("Finish sky\n");
	
	//initGround();
	
	printf("Finish ground\n");
	printf("==========END============");

	/*set red pawns positions*/
    models[PAWN_RED_1] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_1]->setPosition(Vector3(-44,8,31));
    models[PAWN_RED_2] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_2]->setPosition(Vector3(-31,8,31));
    models[PAWN_RED_3] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_3]->setPosition(Vector3(-19,8,31));
    models[PAWN_RED_4] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_4]->setPosition(Vector3(-6,8,31));
    models[PAWN_RED_5] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_5]->setPosition(Vector3(6,8,31));
    models[PAWN_RED_6] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_6]->setPosition(Vector3(19,8,31));
    models[PAWN_RED_7] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_7]->setPosition(Vector3(31,8,31));
    models[PAWN_RED_8] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_8]->setPosition(Vector3(44,8,31));
}

void GameScene::initSky(){
	sky         = new ExtraModel();
	sky->loadModel("Models/sky.obj");
}
void GameScene::initGround(){
	ground = new ExtraModel();
	ground->loadModel("Models/ground.obj");
	ground->setPosition(Vector3(0, 1, 0));
}
void GameScene::loop()
{
	drawSence();
}

void GameScene::drawCells(){
	for(int i = 0; i < BOARD_SIZE; i++){
		for(int j = 0; j < BOARD_SIZE; j++){
			if(allCells[i][j]->mVisible){
				allCells[i][j]->drawModel();
			}
		}
	}
}
void GameScene::drawSence(){

	/*float _ambient[4] = {1, 1, 1, 1};
	glLightfv(GL_LIGHT0, GL_AMBIENT,  _ambient);
	sky->drawModel();
	Light::inst().setAmbient();
	*/
	//ground->drawModel();
	

	pawnRedTempModel->drawModel();
    for(int i = 0 ; i < 8 ; i++){
        models[i] ->drawModel();
    }
	board->drawModel();

	//drawCells();
	//Debug light
	Light::inst().setPosition(lightPosition[0], lightPosition[1], lightPosition[2], lightPosition[3]);
	Light::inst().drawLightSource(lightAngle, lightHeight);

	//Debug ray
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	Vector3 a = mViewRay.origin + 100*mViewRay.direction;
	glVertex3f(mViewRay.origin.x, mViewRay.origin.y, mViewRay.origin.z);
	glVertex3f(a.x, a.y, a.z);
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

GameScene::~GameScene(void)
{

}
