#ifndef _CG_GAME_SCENE_H_
#define _CG_GAME_SCENE_H_

#define BOARD_SIZE 8

#include "../Entities/BaseModel.h"
#include "../Entities/LogicGame.h"
#include "../Entities/Sprite2D.h"
#include "../Entities/ExtraModel.h"
#include "../Control/Camera.h"
#include "../Control/Graphic.h"

class GameScene
{

public:
	GameScene(void);
	~GameScene(void);

	static GameScene& inst();
	//Lighting
	GLfloat lightPosition[4];
	float lightAngle, lightHeight;
    //Light* light;
	Ray mViewRay;

	LogicGame* logic;

	//64 cell
	ExtraModel* allCells[BOARD_SIZE][BOARD_SIZE];

	BaseModel* pawnRedTempModel;

    BaseModel* models[32];

	BaseModel* board;
	ExtraModel* sky;
	ExtraModel* ground;

	ExtraModel* cell;

	float yCir;

	void initEnties();
	void initBoardCells();
	void initSky();
	void initGround();
    void initChessPiecesModels();
	void loop();
	void drawSence();
	void drawCells();

	void processMouseBegan(int x, int y);
	void processMouseEnded(int x, int y);
	void processMousePassiveMotion(int x, int y);
	void processKeyBoard(unsigned key, int x, int y);
    
    int getSelectedIndex(int mouse_x, int mouse_y);

    int prevSelectedChestPieceIndex;
    
    ExtraModel* currentSelectedCell;
    ExtraModel*  prevSelectedCell;

    Vector3 tween(Vector3 A, Vector3 B, float t);
    float t; //tweening factor
    int mode;

    void moveChestPieceOutTheBoard(ExtraModel* boardcell);
};

#endif // !_CG_GAME_SCENE_H_

