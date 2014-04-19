#include "GameSence.h"
#include "Piece.h"

void GameScene::initPiece(){
	float offsets[3] = {0.0, 0.0, 0.0};
	tmpPi = new Knife();
	tmpPi->loadModel("Models/Board.obj");
	tmpPi->setAnchorPoint(Vector3(0, 0, 0));
	tmpPi->setPosition(Vector3(0, 0, 0));
	printf("Height = %f\n", tmpPi->getHeight());
	printf("Height = %f\n", tmpPi->getHeight());
}

GameScene::GameScene(void)
{
  srand(time(NULL));
  font = GLUT_BITMAP_8_BY_13;
  lightPosition[0] = 0;
  lightPosition[1] = 20;
  lightPosition[2] = 0;
  lightPosition[3] = 0;
  lightAngle = 90.0;
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
	/*lightPosition[0] = 15*cos(lightAngle);
	lightPosition[1] = lightHeight;
	lightPosition[2] = 15*sin(lightAngle);*/
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
	/*tmpPi->highlight(!tmpPi->isHighlight());
	tmpPi->shadow(!tmpPi->isShadow());
	tmpPi->selected(!tmpPi->isSelected());*/
	int index = identifyModelClicked(x, y);
	bool texture = tmpPi->getEnableTextures();
	printf("enable texture: %d\n", texture);
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

	// Calculate origin and vector of clicked-ray
	Vector4 rayOrigin = Vector4()*inverseModelViewMatrix;
	Vector3 rayVec = Vector3(x, y, -Graphic::inst().zNear)*inverseModelViewMatrix;

	//cout << rayOrigin.toString();

	mViewRay.set(rayOrigin.toVector3(), rayVec);
	int index = -1;
		// checking click-ray intersected with piece
	if (mViewRay.hasIntersected(tmpPi->boundingbox()))
	{
		printf("Intersected\n");
		index = 1;
	}
	return 1;
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
