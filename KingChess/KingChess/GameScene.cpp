#include "GameSence.h"
#include "Piece.h"

bool allMoveIllegal = true;
bool noPieceInTheGame = true;
int selectedIndex = -1;
Piece* targetPiece = NULL;

GameScene::GameScene(void)
{
  srand(time(NULL));

  for (int i = 0; i < 4; i++)
	mEnablePiece[i] = true;

  mPieceMovingState = MOVE_ILLEGAL;

  mAutoCam = true;
  
  lightPosition[0] = 0;
  lightPosition[1] = 75;
  lightPosition[2] = 0;
  lightPosition[3] = 1;
  lightAngle = 0.0;
  lightHeight = 20;

  font = GLUT_BITMAP_8_BY_13;

  mPlayerTurn = TURN_RED;
  mTries = 0;

  Vector3 start[] = {Vector3(-16, 0, -16),
                     Vector3(-16, 0, -20),
                     Vector3(-20, 0, -20),
                     Vector3(-20, 0, -16),      // RED
  
                     Vector3(16, 0, -16),
                     Vector3(16, 0, -20),
                     Vector3(20, 0, -20),
                     Vector3(20, 0, -16),       // BLUE

                     Vector3(16, 0, 16),
                     Vector3(16, 0, 20),
                     Vector3(20, 0, 20),
                     Vector3(20, 0, 16),        // GREEN

                     Vector3(-16, 0, 16),
                     Vector3(-16, 0, 20),
                     Vector3(-20, 0, 20),
                     Vector3(-20, 0, 16),       // YELLOW
  };
  float startDirection[] = { -90, -90, -90, -90,  // RED
                             180, 180, 180, 180,  // BLUE
                              90,  90,  90,  90,  // GREEN
                               0,   0,   0,   0}; // YELLOW
  for (int i = 0; i < 16; i++)
  {
    start[i].y = 2;
    mStartPos[i].position = start[i];
    mStartPos[i].direction = startDirection[i];
  }


  Vector3 home[] = {  Vector3(-16, 3, 0),
                      Vector3(-12, 4, 0),
                      Vector3(-8, 5, 0),
                      Vector3(-4, 6, 0),        // RED

                      Vector3(0, 3, -16),
                      Vector3(0, 4, -12),
                      Vector3(0, 5, -8),  
                      Vector3(0, 6, -4),        // BLUE

                      Vector3(16, 3, 0),
                      Vector3(12, 4, 0),
                      Vector3(8, 5, 0),
                      Vector3(4, 6, 0),         // GREEN

                      Vector3(0, 3, 16),
                      Vector3(0, 4, 12),
                      Vector3(0, 5, 8),
                      Vector3(0, 6, 4)          // YELLOW
  };
  float homeDirection[] = {  0,   0,   0,   0,  // RED
                           -90, -90, -90, -90,  // BLUE
                           180, 180, 180, 180,  // GREEN
                            90,  90,  90,  90   // YELLOW
  };
  //memcpy(mHome, stable, sizeof(stable));
  for (int i = 0; i < 16; i++)
  {
    mHome[i] = Field(home[i], homeDirection[i]);
  }

  /* ROAD
                x  x  G
                x     x
                x     x
                x     x
    B  x  x  x  x     x  x  x  x  x
    x                             x
    x  x  x  x  x     x  x  x  x  Y
                x     x
                x     x
                x     x
                R  x  x
  */

  Vector3 road[] = { Vector3(-20, 0, -4),      // RED START

                  Vector3(-16, 0, -4),
                  Vector3(-12, 0, -4),
                  Vector3(-8, 0, -4),
                  Vector3(-4, 0, -4),
                  Vector3(-4, 0, -8),
                  Vector3(-4, 0, -12),
                  Vector3(-4, 0, -16),

                  Vector3(-4, 0, -20),
                  Vector3(0, 0, -20),
                  Vector3(4, 0, -20),       // BLUE START

                  Vector3(4, 0, -16),
                  Vector3(4, 0, -12),
                  Vector3(4, 0, -8),
                  Vector3(4, 0, -4),
                  Vector3(8, 0, -4),
                  Vector3(12, 0, -4),
                  Vector3(16, 0, -4),

                  Vector3(20, 0, -4),
                  Vector3(20, 0, 0),
                  Vector3(20, 0, 4),        // GREEN START

                  Vector3(16, 0, 4),
                  Vector3(12, 0, 4),
                  Vector3(8, 0, 4),
                  Vector3(4, 0, 4),
                  Vector3(4, 0, 8),
                  Vector3(4, 0, 12),
                  Vector3(4, 0, 16),

                  Vector3(4, 0, 20),
                  Vector3(0, 0, 20),
                  Vector3(-4, 0, 20),       // YELLOW START

                  Vector3(-4, 0, 16),
                  Vector3(-4, 0, 12),
                  Vector3(-4, 0, 8),
                  Vector3(-4, 0, 4),
                  Vector3(-8, 0, 4),
                  Vector3(-12, 0, 4),
                  Vector3(-16, 0, 4),

                  Vector3(-20, 0, 4),
                  Vector3(-20, 0, 0)
  };
  float roadDiretion[] = {   0,   0,   0,   0,
                            90,  90,  90,  90,
                             0,   0,
                           -90, -90, -90, -90,
                             0,   0,   0,   0,
                           -90, -90,
                           180, 180, 180, 180,
                           -90, -90, -90, -90,
                           180, 180,
                            90,  90,  90,  90, 
                           180, 180, 180, 180,
                            90,  90
  };

  //memcpy(mFields, r, sizeof(r));
  for (int i = 0; i < 40; i++)
  {
    road[i].y = 2;         
    mFields[i] = Field(road[i], roadDiretion[i]);
  }

  int c[] = { 0, 4, 8, 10, 14, 18, 20, 24, 28, 30, 34, 38 };
  memcpy(mConnerIndex, c, sizeof(c));
  int x;
  initAllPieces();
}

GameScene& GameScene::inst()
{
  static GameScene Instance;
  return Instance;
}

void GameScene::initBoard()
{  
}

void GameScene::initPiece()
{
  tmpPiece = new Piece();
  
  tmpPiece->loadModel("Models/knight.obj");
  tmpPiece->setAnchorPoint(Vector3(0, -0.5, 0));

}

void GameScene::initAllPieces()
{
  initPiece();
  for (int i = 0; i < 4; i++)
  {
    mPieces[i] = new Piece(tmpPiece);
    mPieces[i]->setPosition(mStartPos[i].position);
    mPieces[i]->setInitPosition(mStartPos[i]);
    mPieces[i]->setType(TURN_RED);
    mPieces[i]->setAngleRotate(-90);

    mPieces[4+i] = new Piece(tmpPiece);
    mPieces[4+i]->setPosition(mStartPos[4+i].position);
    mPieces[4+i]->setInitPosition(mStartPos[4+i]);
    mPieces[4+i]->setType(TURN_BLUE);
    mPieces[4+i]->setAngleRotate(180);

    mPieces[8+i] = new Piece(tmpPiece);
    mPieces[8+i]->setPosition(mStartPos[8+i].position);
    mPieces[8+i]->setInitPosition(mStartPos[8+i]);
    mPieces[8+i]->setType(TURN_GREEN);
    mPieces[8+i]->setAngleRotate(90);

    mPieces[12+i] = new Piece(tmpPiece);
    mPieces[12+i]->setPosition(mStartPos[12+i].position);
    mPieces[12+i]->setInitPosition(mStartPos[12+i]);
    mPieces[12+i]->setType(TURN_YELLOW);
  }


  tmpPiece = NULL;//delete temp
}

void GameScene::drawSence()
{
  // Save current matrix state
  glPushMatrix();
  for (int i = 0; i < 4; i++)
  {
    if (mEnablePiece[0])
      mPieces[i]->drawModel(); 

    if (mEnablePiece[1])
      mPieces[4+i]->drawModel(); 

    if (mEnablePiece[2])
      mPieces[8+i]->drawModel(); 

    if (mEnablePiece[3])
      mPieces[12+i]->drawModel(); 
  }
  glPopMatrix();
}

void GameScene::loop()
{
  //update();
  drawSence();
}

int GameScene::getModelPositionIndex( Vector3 pPos , Field pArray[], int pSize)
{
  for (int i = 0; i < pSize; i++)
    if (pPos == pArray[i].position)
      return i;

  return -1;
}

void GameScene::movePiece(int arrayIndex)
{
  if (!mDieIsThrown)
    return;

  Piece* mod = mPieces[arrayIndex];
  mod->attack(false);
  Turn playerTurn = mPlayerTurn;

  if (mod != NULL && mod->getType() == mPlayerTurn)
  {
    vector<Field> target;

    int k = arrayIndex % 4;

    if (mPredictMoveState[k] == MOVE_ILLEGAL)
      return;
    if (mPredictMoveState[k] == MOVE_NORMAL || mPredictMoveState[k] == MOVE_HOME_OUTSIDE)
    {
      int index = getModelPositionIndex(mod->getPosition(), mFields, 40);
      int predictIndex;
      if (mPredictMoveState[k] == MOVE_NORMAL)
        predictIndex = getModelPositionIndex(mPredictPosition[k]->position, mFields, 40);
      else if (mPredictMoveState[k] == MOVE_HOME_OUTSIDE)
      {
        predictIndex = mPlayerTurn*10-1;
        predictIndex = predictIndex == -1 ? 39 : predictIndex;
      }

      // Piece is at under Home
      if (predictIndex == index)
      {

      }
      else if (predictIndex > index) // Move with corner
      {
        for (int i = 0; i < 12; i++)
          if (index < mConnerIndex[i] && mConnerIndex[i] < predictIndex )
            target.push_back(mFields[mConnerIndex[i]]);
      }
      else // corner at index 38 & 0
      {
        if (index < mConnerIndex[11])
          target.push_back(mFields[mConnerIndex[11]]);
        if (predictIndex > mConnerIndex[0])
          target.push_back(mFields[mConnerIndex[0]]);
      }
      target.push_back(mFields[predictIndex]);

      for (int i = 0; i < target.size(); i++)
      {
        int predictIndex = getModelPositionIndex(target[i].position, mFields, 40);
        predictIndex = predictIndex + 1 == 40 ? 0 : predictIndex + 1;

        if (predictIndex == mPlayerTurn*10)
        {
          target[i].direction = mHome[4*mPlayerTurn].direction;
        }
      }

      mFields[index].piece = NULL;

      if (mPredictMoveState[k] == MOVE_NORMAL)
      {
        mFields[predictIndex].piece = mod;
      }
      else if (mPredictMoveState[k] == MOVE_HOME_OUTSIDE)
      {
        target.push_back(*mPredictPosition[k]);

        mPredictPosition[k]->piece = mod;
        mPredictPosition[k]->piece->setArea(AREA_HOME);
      }

      mod->jumpTo(target, mPredictMoveState[k]);
      mPieceMovingState = mPredictMoveState[k];
      tmpPiece = mod;
    }
    else
    {
      target.push_back(*mPredictPosition[k]);
      int predictIndex = getModelPositionIndex(target[0].position, mFields, 40);
      if (predictIndex%10 == 9)
      {
        int div = (predictIndex+1)/10;
        div = div == 4 ? 0 : div;
        target[0].direction = mHome[4*div].direction;
      }

      if (mPredictMoveState[k] == MOVE_ATTACK)
      {
        int index = getModelPositionIndex(mod->getPosition(), mFields, 40);

        mPredictPosition[k]->piece->setArea(AREA_OUT);
        targetPiece = mPredictPosition[k]->piece;
        targetPiece->defence(false);

        mFields[index].piece = NULL;
        mPredictPosition[k]->piece = mod;
      }

      if (mPredictMoveState[k] == MOVE_START_ATTACK)
      {
        mPredictPosition[k]->piece->setArea(AREA_OUT);
        targetPiece = mPredictPosition[k]->piece;

        mPredictPosition[k]->piece = mod;
        mPredictPosition[k]->piece->setArea(AREA_GAME);
      }

      if (mPredictMoveState[k] == MOVE_START)
      {
        mPredictPosition[k]->piece = mod;
        mPredictPosition[k]->piece->setArea(AREA_GAME);
      }

      if (mPredictMoveState[k] == MOVE_HOME_INSIDE)
      {
        int index = getModelPositionIndex(mod->getPosition(), mHome, 16);

        mHome[index].piece = NULL;
        mPredictPosition[k]->piece = mod;
      }

      mod->jumpTo(target, mPredictMoveState[k]);
      mPieceMovingState = mPredictMoveState[k];
      tmpPiece = mod;
    }
  }

  /*---------------- FIND THE WINNER ^^ -------------------*/
  mFullHome = true;
  for (int i = playerTurn*4; i < playerTurn*4+4; i++)
  {
    if (mHome[i].piece == NULL)
    {
      mFullHome = false;
      break;
    }
  }

  if (mFullHome)
  {
    mWinner = playerTurn;
    mIsGoHome[playerTurn] = true;
  }
}


void GameScene::update()
{
  // Checking if die is displayed and show the number to user
  if (tmpPiece && tmpPiece->getState() == MODEL_ATTACK)
  {
    mPieceMovingState = MOVE_NORMAL;
    Camera::inst().R = Camera::Radius;
    Camera::inst().at = Camera::origin;
    mUserViewAngle = calcUserViewAngle(tmpPiece->getPosition());
    Camera::inst().theta = mUserViewAngle;
    Camera::inst().updateAngle();

    //tmpPiece = NULL;

    if (targetPiece)
    {
      targetPiece->setPosition(targetPiece->getInitPosition().position);
      targetPiece->setAngleRotate(targetPiece->getInitPosition().direction); 
    }
  }

  if (mPieceMovingState == MOVE_NORMAL || mPieceMovingState == MOVE_START ||
    mPieceMovingState == MOVE_HOME_INSIDE || mPieceMovingState == MOVE_HOME_OUTSIDE)
  {
    mUserViewAngle = calcUserViewAngle(tmpPiece->getPosition());
  }
  else if (mPieceMovingState == MOVE_ATTACK || mPieceMovingState == MOVE_START_ATTACK)
  {
    Camera::inst().theta += 0.05;
    Camera::inst().updateAngle();
    mUserViewAngle = Camera::inst().theta;

    Camera::inst().R = 25;
    Camera::inst().at = tmpPiece->getPosition();
  }
  else
  {
    Camera::inst().R = Camera::Radius;
    Camera::inst().at = Camera::origin;
    if (tmpPiece)
    {
      mUserViewAngle = calcUserViewAngle(tmpPiece->getPosition());
      Camera::inst().theta = mUserViewAngle;
      Camera::inst().updateAngle();
      tmpPiece = NULL;
    }
  }

  if (mAutoCam)
  {
    float curTheta = Camera::inst().theta;
    float curPhi = Camera::inst().phi;

    if (curTheta - mUserViewAngle > Math::PI)
    {
      curTheta -= Math::TWO_PI;
    }
    else if (curTheta - mUserViewAngle < -Math::PI)
    {
      curTheta += Math::TWO_PI;
    }

    if (abs(curPhi - Math::PI/3) > 0.01)
    {
      float deltaPhi = abs(curPhi - Math::PI/3)/30;
      deltaPhi = deltaPhi > 0.01 ? deltaPhi : 0.005;
      if (curPhi > Math::PI/3)
        Camera::inst().phi -= deltaPhi;
      else
        Camera::inst().phi += deltaPhi;

      Camera::inst().updateAngle();
    }
    if (abs(curTheta - mUserViewAngle) > 0.05)
    {
      float deltaTheta = abs(curTheta - mUserViewAngle)/30;
      deltaTheta = deltaTheta > 0.02 ? deltaTheta : 0.015;
      if (curTheta > mUserViewAngle)
        Camera::inst().theta -= deltaTheta;
      else
        Camera::inst().theta += deltaTheta;

      Camera::inst().updateAngle();
    }
    if (abs(curPhi - Math::PI/3) <= 0.01 && abs(curTheta - mUserViewAngle) <= 0.05)
    {
      mAutoCam = false;
    }
  }
}

// Disable some Players
void GameScene::setDisablePiece( int index )
{
  mEnablePiece[index] = false;
  if (mPlayerTurn == index)
  {
    for (int i = 0; i < 4; i++)
    {
      // Change start turn if the currently is disabled
      if (!mEnablePiece[i])
      {
        mPlayerTurn = (Turn)(i+1 > 4 ? 0 : i+1);
        break;
      }
    } 
  }
}

void GameScene::processMouseBegan( int x, int y )
{
	int index = identifyModelClicked(x, y);
	printf("at (%d, %d) is piece number %d \n", x , y, index);
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

  Piece** piecesArray = getPiecesArray();

  float disMin = -1;
  int index = -1;

  for (int i = 0; i < 16; i++)
  {
    // checking click-ray intersected with piece
    if (mViewRay.hasIntersected(piecesArray[i]->boundingbox()))
    {
      //cout << "intersected" << endl;
      
      Vector3 a = Camera::inst().eye;
      Vector3 b = piecesArray[i]->getPosition();
      float dist = (a-b).magnitude();

      // get the nearest piece
      if (disMin < 0)
      {
        disMin = dist;
        index = i;
      }
      else if (dist < disMin)
      {
        disMin = dist;
        index = i;
      }
    }
  }

  return index;
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
