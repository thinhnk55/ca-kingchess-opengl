#include "GameSence.h"
#include "../Entities/LogicGame.h"
#include "../Constant.h"


GameScene::GameScene(void)
{
	logic = new LogicGame();
	yCir = -15;
	lightPosition[0] = 0;
	lightPosition[1] = 100;
	lightPosition[2] = 0;
	lightPosition[3] = 1;
	lightAngle = 0.0;
	lightHeight = 100;

	initEnties();

    prevSelected = 0;
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
	
	initSky();

	printf("Finish sky\n");
	
	initGround();
	
	printf("Finish ground\n");
	printf("==========END============");

	/*set red pawns positions*/
    models[PAWN_RED_1] = new BaseModel(pawnRedTempModel);
    models[PAWN_RED_1]->setPosition(Vector3(-44,8,31));
   /* models[PAWN_RED_2] = new BaseModel(pawnRedTempModel);
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
    models[PAWN_RED_8]->setPosition(Vector3(44,8,31));*/

    /*set red bishops positions*/
    models[BISHOP_RED_1] = new BaseModel();
    models[BISHOP_RED_1]->loadModel("Models/Bishop.obj");
    models[BISHOP_RED_1]->setPosition(Vector3(-19,9,44));
   /* models[BISHOP_RED_2] = new BaseModel(models[BISHOP_RED_1]);
    models[BISHOP_RED_2]->setPosition(Vector3(19,9,44));*/

    /*set red knights positions*/
    models[KNIGHT_RED_1] = new BaseModel();
    models[KNIGHT_RED_1]->loadModel("Models/knight.obj");
    models[KNIGHT_RED_1]->setPosition(Vector3(-32,9,44));
    models[KNIGHT_RED_1]->setAngleRotate(-90);
   /* models[KNIGHT_RED_2] = new BaseModel(models[KNIGHT_RED_1]);
    models[KNIGHT_RED_2]->setPosition(Vector3(32,9,44));*/

    /*set red rooks positions*/
    models[ROOK_RED_1] = new BaseModel();
    models[ROOK_RED_1]->loadModel("Models/Rook.obj");
    models[ROOK_RED_1]->setPosition(Vector3(-44,9,44));
    /*models[ROOK_RED_2] = new BaseModel(models[ROOK_RED_1]);
    models[ROOK_RED_2]->setPosition(Vector3(44,9,44));*/

    /*set red queen positions*/
    models[QUEEN_RED] = new BaseModel();
    models[QUEEN_RED]->loadModel("Models/Queen.obj");
    models[QUEEN_RED]->setPosition(Vector3(-6,9,44));

    /*set red king positions*/
    models[KING_RED] = new BaseModel();
    models[KING_RED]->loadModel("Models/King.obj");
    models[KING_RED]->setPosition(Vector3(6,10,44));

    /*set blue pawns positions*/
    models[PAWN_BLUE_1] = new BaseModel();
    models[PAWN_BLUE_1]->loadModel("Models/PawnBlue.obj");
    models[PAWN_BLUE_1]->setPosition(Vector3(-44,8,-31));
    /*models[PAWN_BLUE_2] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_2]->setPosition(Vector3(-31,8,-31));
    models[PAWN_BLUE_3] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_3]->setPosition(Vector3(-19,8,-31));
    models[PAWN_BLUE_4] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_4]->setPosition(Vector3(-6,8,-31));
    models[PAWN_BLUE_5] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_5]->setPosition(Vector3(6,8,-31));
    models[PAWN_BLUE_6] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_6]->setPosition(Vector3(19,8,-31));
    models[PAWN_BLUE_7] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_7]->setPosition(Vector3(31,8,-31));
    models[PAWN_BLUE_8] = new BaseModel(models[PAWN_BLUE_1]);
    models[PAWN_BLUE_8]->setPosition(Vector3(44,8,-31));*/

    /*set blue rooks positions */
    models[ROOK_BLUE_1] = new BaseModel();
    models[ROOK_BLUE_1]->loadModel("Models/RookBlue.obj");
    models[ROOK_BLUE_1]->setPosition(Vector3(-44,9,-44));
   /* models[ROOK_BLUE_2] = new BaseModel(models[ROOK_BLUE_1]);
    models[ROOK_BLUE_2]->setPosition(Vector3(44,9,-44));*/

    /*set blue knights positions*/
    models[KNIGHT_BLUE_1] = new BaseModel();
    models[KNIGHT_BLUE_1]->loadModel("Models/knightBlue.obj");
    models[KNIGHT_BLUE_1]->setPosition(Vector3(-32,9,-44));
    models[KNIGHT_BLUE_1]->setAngleRotate(90);
   /* models[KNIGHT_BLUE_2] = new BaseModel(models[KNIGHT_BLUE_1]);
    models[KNIGHT_BLUE_2]->setPosition(Vector3(32,9,-44));*/

    /*set blue bishops positions*/
    models[BISHOP_BLUE_1] = new BaseModel();
    models[BISHOP_BLUE_1]->loadModel("Models/BishopBlue.obj");
    models[BISHOP_BLUE_1]->setPosition(Vector3(-19,9,-44));
   /* models[BISHOP_BLUE_2] = new BaseModel(models[BISHOP_BLUE_1]);
    models[BISHOP_BLUE_2]->setPosition(Vector3(19,9,-44));*/

    /*set blue queen positions*/
    models[QUEEN_BLUE] = new BaseModel();
    models[QUEEN_BLUE]->loadModel("Models/QueenBlue.obj");
    models[QUEEN_BLUE]->setPosition(Vector3(-6,9,-44));

    /*set blue king positions*/
    models[KING_BLUE] = new BaseModel();
    models[KING_BLUE]->loadModel("Models/KingBlue.obj");
    models[KING_BLUE]->setPosition(Vector3(6,10,-44));
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

	float _ambient[4] = {1, 1, 1, 1};
	glLightfv(GL_LIGHT0, GL_AMBIENT,  _ambient);
	sky->drawModel();
	Light::inst().setAmbient();
	
	ground->drawModel();
	

	pawnRedTempModel->drawModel();

    for(int i = 0 ; i < 32 ; i++){
        if(models[i] != NULL)
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

    for(int i = 0 ; i < 32 ; i++){

        if(models[i] != NULL && mViewRay.hasIntersected(models[i]->boundingbox())){
            
            currentDist = (Camera::inst().eye - models[i]->getPosition()).magnitude();

            if(minDist == -1){
                minDist = currentDist;
                index = i;
            }

            else{
                if(currentDist <= minDist){
                    minDist = currentDist;
                    index = i;
                }
            }
        }
            
    }
     
    if(index != -1){   
        models[prevSelected]->mDrawKnife = false;
        models[index]->mDrawKnife = true;
        prevSelected = index;
    }
    else
        models[prevSelected]->mDrawKnife = false;
    return index;
}

GameScene::~GameScene(void)
{

}
