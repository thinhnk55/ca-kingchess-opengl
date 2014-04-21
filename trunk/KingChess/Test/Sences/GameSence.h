#ifndef _CG_GAME_SCENE_H_
#define _CG_GAME_SCENE_H_

#define BOARD_SIZE 8

#include "../Entities/BaseModel.h"
#include "../Entities/LogicGame.h"
#include "../Entities/Sprite2D.h"
#include "../Entities/ExtraModel.h"


class GameScene
{

public:
	GameScene(void);
	~GameScene(void);

	static GameScene& inst();
	//Lighting
	GLfloat lightPosition[4];
	float lightAngle, lightHeight;
	Ray mViewRay;

	LogicGame* logic;

	//64 cell
	ExtraModel* allCells[BOARD_SIZE][BOARD_SIZE];

	BaseModel* model;
	BaseModel* board;
	ExtraModel* sky;
	ExtraModel* ground;

	ExtraModel* cell;

	float yCir;

	void initEnties();
	void initSprites();
	void initSky();
	void initGround();
	void loop();
	void drawSence();
	void drawCells();

	void processMouseBegan(int x, int y);
	void processMouseEnded(int x, int y);
	void processMousePassiveMotion(int x, int y);
	void processKeyBoard(unsigned key, int x, int y);


	void processKeyBoard();
};

#endif // !_CG_GAME_SCENE_H_

