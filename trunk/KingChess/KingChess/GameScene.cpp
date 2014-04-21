#include "GameSence.h"
#include "Piece.h"

void GameScene::initPiece(){
	float offsets[3] = {0.0, 0.0, 0.0};
	tmpPi = new Piece();
	tmpPi->loadModel("Models/knight.obj");
	tmpPi->setAnchorPoint(Vector3(0, 0, 0));
	tmpPi->setPosition(Vector3(0, 4.0, 0));
	

	board = new Piece();
	board->loadModel("Models/board.obj");
	board->setAnchorPoint(Vector3(0, 0.0, 0));
	board->setPosition(Vector3(0, -20.0, 0));
	board->shadow(false);
}

GameScene::GameScene(void)
{
  srand(time(NULL));
  font = GLUT_BITMAP_8_BY_13;
  lightPosition[0] = 0;
  lightPosition[1] = 25;
  lightPosition[2] = 0;
  lightPosition[3] = 0;
  lightAngle = 60.0;
  lightHeight = 25;
  initPiece();
}

GameScene& GameScene::inst()
{
  static GameScene Instance;
  
  return Instance;
}


void GameScene::loop()
{
  update();
  drawSence();
}
void GameScene::drawSence(){
	glEnable(GL_LIGHTING);	
	glPushMatrix();
		tmpPi->drawModel();
		board->drawModel();
	glPopMatrix();

	//Debug light
	lightPosition[0] = 25*cos(lightAngle);
	lightPosition[1] = lightHeight;
	lightPosition[2] = 25*sin(lightAngle);
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
void GameScene::update()
{
  
}



void GameScene::processMouseBegan( int x, int y )
{
	int index = identifyModelClicked(x, y);
	tmpPi->selected(!tmpPi->isSelected());
	tmpPi->shadow(!tmpPi->isShadow());
}

void GameScene::processMousePassiveMotion( int x, int y )
{

}

// Identify which Piece has been clicked
// Return index of Piece in array
int GameScene::identifyModelClicked( int mouse_x, int mouse_y )
{
	// Get x, y coordinate in zNear plane
	int window_y = mouse_y - Graphic::inst().screenHeight/2;
	double norm_y = double(window_y)/double(Graphic::inst().screenHeight/2);
	int window_x = mouse_x - Graphic::inst().screenWidth/2;
	double norm_x = double(window_x)/double(Graphic::inst().screenWidth/2);

	float aspect = Graphic::inst().screenWidth/Graphic::inst().screenHeight;

	float y = Graphic::inst().near_height * norm_y;
	float x = Graphic::inst().near_height * aspect * norm_x;

	// Get ModelView matrix
	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX , m);

	Matrix4 inverseModelViewMatrix = Matrix4(m).inverse();

	Vector3 rayOrigin = Camera::inst().eye;
	Vector3 rayVec = Vector3(x, y, -Graphic::inst().zNear) * inverseModelViewMatrix;
	mViewRay.set(rayOrigin, rayVec);

	int index = -1;

	if (mViewRay.hasIntersected(tmpPi->boundingbox()))
	{
		index = 1;
	}
	return index;
}

GameScene::~GameScene(void)
{

}
