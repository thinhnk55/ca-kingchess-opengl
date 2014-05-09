#ifndef _LOGIC_GAME_H_
#define _LOGIC_GAME_H_
#include "../Constant.h"
#include "ExtraModel.h"
class LogicGame
{
public:
	Turn turn;

    bool isValidMoving(ExtraModel* firstCell, ExtraModel *secondCell);
    void transformPawnToQueen(ExtraModel* firstCell, ExtraModel *secondCell, int);
    void changeTurn();

	LogicGame();
	~LogicGame();

private:
    bool checkPawnMoveRule(ExtraModel* firstCell, ExtraModel *secondCell,bool isRed);
    bool checkQueenMoveRule(ExtraModel* firstCell, ExtraModel *secondCell);
    bool checkBishopMoveRule(ExtraModel *firstcell, ExtraModel *secondcell);
    bool checkRookMoveRule(ExtraModel *firstcell, ExtraModel *secondcell);
    bool checkKnightMoveRule(ExtraModel *firstcell, ExtraModel *secondcell);
    bool checkKingMoveRule(ExtraModel *firstcell, ExtraModel *secondcell);
    ExtraModel* getBoardCell(int x, int y);
};

#endif
