#include "GameSence.h"
#include "../Entities/LogicGame.h"




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
	model = new BaseModel();
	model->loadModel("Models/pawn.obj");
	model->setPosition(Vector3(0, 8, 0));
	model->setAngleRotate(90.0);
	model->mShadow = true;
	model->mSelected = true;
	model->mDrawKnife = true;
	model->mDrawShield = true;
	model->mVisible = true;
	printf("model Pos = (%f, %f, %f)\n", model->getPosition().x, model->getPosition().y, model->getPosition().z);
	printf("model Anchor point = (%f, %f, %f)\n", model->getAnchorPoint().x, model->getAnchorPoint().y, model->getAnchorPoint().z);

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
	

	model->drawModel();
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
	case 'a':
		model->moveDown(1);
		printf("model Pos = (%f, %f, %f)\n", model->getPosition().x, model->getPosition().y, model->getPosition().z);
		printf("model Anchor point = (%f, %f, %f)\n", model->getAnchorPoint().x, model->getAnchorPoint().y, model->getAnchorPoint().z);
		break;

	case 'z':
		model->moveUp(1);
		printf("model Pos = (%f, %f, %f)\n", model->getPosition().x, model->getPosition().y, model->getPosition().z);
		printf("model Anchor point = (%f, %f, %f)\n", model->getAnchorPoint().x, model->getAnchorPoint().y, model->getAnchorPoint().z);
		break;

	case 'c':
		model->moveLeft(1);
		printf("model Pos = (%f, %f, %f)\n", model->getPosition().x, model->getPosition().y, model->getPosition().z);
		printf("model Anchor point = (%f, %f, %f)\n", model->getAnchorPoint().x, model->getAnchorPoint().y, model->getAnchorPoint().z);
		break;

	case 't':
		model->moveRight(1);
		printf("model Pos = (%f, %f, %f)\n", model->getPosition().x, model->getPosition().y, model->getPosition().z);
		printf("model Anchor point = (%f, %f, %f)\n", model->getAnchorPoint().x, model->getAnchorPoint().y, model->getAnchorPoint().z);
		break;
	case 'd':
		model->moveIn(1);
		printf("model Pos = (%f, %f, %f)\n", model->getPosition().x, model->getPosition().y, model->getPosition().z);
		printf("model Anchor point = (%f, %f, %f)\n", model->getAnchorPoint().x, model->getAnchorPoint().y, model->getAnchorPoint().z);
		break;
	case 'g':
		model->moveOut(1);
		printf("model Pos = (%f, %f, %f)\n", model->getPosition().x, model->getPosition().y, model->getPosition().z);
		printf("model Anchor point = (%f, %f, %f)\n", model->getAnchorPoint().x, model->getAnchorPoint().y, model->getAnchorPoint().z);
		break;
	}
}

GameScene::~GameScene(void)
{

}
