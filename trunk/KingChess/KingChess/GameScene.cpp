#include "GameSence.h"
#include "Piece.h"

void GameScene::initPiece(){
	tmpPi = new Piece();
	tmpPi->loadModel("Models/Rook.obj");
	tmpPi->setColorTint(0.8, 0.0, 0.0);
	tmpPi->setAnchorPoint(Vector3(0, -0.5, 0));
	tmpPi->setPosition(Vector3(-16, 2, -4));
}

GameScene::GameScene(void)
{
  srand(time(NULL));
  font = GLUT_BITMAP_8_BY_13;
  lightPosition[0] = 0;
  lightPosition[1] = 75;
  lightPosition[2] = 0;
  lightPosition[3] = 1;
  lightAngle = 0.0;
  lightHeight = 20;

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
	glPopMatrix();
	//Debug light
	lightPosition[0] = 15*cos(lightAngle);
	lightPosition[1] = lightHeight;
	lightPosition[2] = 15*sin(lightAngle);
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
	printf("Mouse clicked");
	tmpPi->highlight(!tmpPi->isHighlight());
	tmpPi->shadow(!tmpPi->isShadow());
	tmpPi->selected(true);
}

void GameScene::processMousePassiveMotion( int x, int y )
{

}

// Identify which Piece has been clicked
// Return index of Piece in array
int GameScene::identifyModelClicked( int mouse_x, int mouse_y )
{
	return -1;
}


float GameScene::calcUserViewAngle( Vector3 pV )
{
  mAutoCam = true;

  Vector2 viewVector = Vector2(pV.x, pV.z) - Vector2(Camera::inst().at.x, Camera::inst().at.z);
  float angle = acos(Vector2::dot(viewVector, Camera::inst().zeroViewVector)/
    (viewVector.magnitude() * Camera::inst().zeroViewVector.magnitude()));

  if (viewVector.x >= 0)
    return angle;
  else
    return -angle;
}

GameScene::~GameScene(void)
{

}
