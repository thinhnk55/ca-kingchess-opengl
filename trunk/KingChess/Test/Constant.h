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
/*red pieces */
#define PAWN_RED_1 8
#define PAWN_RED_2 9
#define PAWN_RED_3 10
#define PAWN_RED_4 11
#define PAWN_RED_5 12
#define PAWN_RED_6 13
#define PAWN_RED_7 14
#define PAWN_RED_8 15
#define BISHOP_RED_1 2
#define BISHOP_RED_2 5
#define KNIGHT_RED_1 1
#define KNIGHT_RED_2 6
#define ROOK_RED_1 0
#define ROOK_RED_2 7
#define QUEEN_RED 3
#define KING_RED 4

/*blue pieces*/
#define PAWN_BLUE_1 16
#define PAWN_BLUE_2 17
#define PAWN_BLUE_3 18
#define PAWN_BLUE_4 19
#define PAWN_BLUE_5 20
#define PAWN_BLUE_6 21
#define PAWN_BLUE_7 22
#define PAWN_BLUE_8 23
#define ROOK_BLUE_1 24
#define ROOK_BLUE_2 31
#define KNIGHT_BLUE_1 25
#define KNIGHT_BLUE_2 30
#define BISHOP_BLUE_1 26
#define BISHOP_BLUE_2 29
#define QUEEN_BLUE 27
#define KING_BLUE 28

#define MOVING 1
#define IDLE 0
#define FIGHT 2
enum Turn
{
	BLACK, 
	WHITE
};

#endif // !_CG_CONSTANTS_H_
