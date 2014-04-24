#ifndef _CG_CONSTANTS_H_
#define _CG_CONSTANTS_H_

#define GLSYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }
;

#define PIECE_CIRCLE_SIZE 1.5

/*****************

DEFINE INDEX OF MODELS

*****************/
#define PAWN_RED_1 0
#define PAWN_RED_2 1
#define PAWN_RED_3 2
#define PAWN_RED_4 3
#define PAWN_RED_5 4
#define PAWN_RED_6 5
#define PAWN_RED_7 6
#define PAWN_RED_8 7

enum Turn
{
	BLACK, 
	WHITE
};

#endif // !_CG_CONSTANTS_H_
