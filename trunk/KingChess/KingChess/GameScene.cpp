#include "GameSence.h"
#include "Piece.h"

GameScene::GameScene(void)
{
  srand(time(NULL));
  font = GLUT_BITMAP_8_BY_13;
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
	
}
void GameScene::update()
{
  
}



void GameScene::processMouseBegan( int x, int y )
{
	printf("Mouse clicked");
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
