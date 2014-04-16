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

public:
	void* font;
	Turn mWinner;
	Ray mViewRay;

	float mUserViewAngle;
	float mouse_x;
	float mouse_y;
	Piece* tmpPi;

	void initPiece();
	void drawSence();
	int getModelPositionIndex(Vector3 pPos, Field pArray[], int pSize);

	int identifyModelClicked(int mouse_x, int mouse_y);
	float calcUserViewAngle(Vector3 pV);

	GLfloat lightPosition[4];
	float lightAngle, lightHeight;

	Turn mPlayerTurn;
	bool mAutoCam;

	GameScene(void);
	~GameScene(void);

	static GameScene& inst();

	void loop();

	void processMouseBegan(int x, int y);
	void processMouseEnded(int x, int y);
	void processMousePassiveMotion(int x, int y);

	virtual void update();
};

#endif // !_CG_GAME_SCENE_H_

