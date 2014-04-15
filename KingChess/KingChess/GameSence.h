#ifndef _CG_GAME_SCENE_H_
#define _CG_GAME_SCENE_H_


#include <string>

#include "Scene.h"
#include "Piece.h"
#include "Light.h"
#include "Graphic.h"
#include "Constants.h"
#include "Camera.h"

class GameScene : public Scene
{
	void* font;
	// Model
	Piece*              mPieces[32]; // 0-15:Black, 16-31:White
	Piece*              tmpPiece;

	// Disable player
	bool mEnablePiece[2];

	// Array of Position in board
	Field mStartPos[16];
	Field mFields[40];
	Field mHome[16];
	int mConnerIndex[12];

	// Predict Position and MoveState after roll die
	Field* mPredictPosition[4];
	MoveState mPredictMoveState[4];
	bool mIsGoHome[4];

	int mDieNumber;
	int mTries;
	bool mDieIsThrown;
	bool mustBeStart;
	bool mFullHome;
	MoveState mPieceMovingState;

	Turn mWinner;
	Ray mViewRay;

	float mUserViewAngle;

	void drawSence();
	int getModelPositionIndex(Vector3 pPos, Field pArray[], int pSize);

	int identifyModelClicked(int mouse_x, int mouse_y);
	float calcUserViewAngle(Vector3 pV);

public:
	GLfloat lightPosition[4];
	float lightAngle, lightHeight;

	bool mDieIsDrawn;
	Turn mPlayerTurn;
	bool mAutoCam;

	GameScene(void);
	~GameScene(void);

	static GameScene& inst();

	void initBoard();
	void initPiece();
	void initAllPieces();

	Piece** getPiecesArray(){
		return mPieces;
	}


	void resetBoard();
	void loop();
	void movePiece(int index);

	void setDisablePiece(int index);

	void processMouseBegan(int x, int y);
	void processMouseEnded(int x, int y);
	void processMousePassiveMotion(int x, int y);

	virtual void update();
};

#endif // !_CG_GAME_SCENE_H_

