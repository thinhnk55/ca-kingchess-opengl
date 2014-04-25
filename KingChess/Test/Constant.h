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
#define PAWN_RED_1 0
#define PAWN_RED_2 1
#define PAWN_RED_3 2
#define PAWN_RED_4 3
#define PAWN_RED_5 4
#define PAWN_RED_6 5
#define PAWN_RED_7 6
#define PAWN_RED_8 7
#define BISHOP_RED_1 10
#define BISHOP_RED_2 13
#define KNIGHT_RED_1 9
#define KNIGHT_RED_2 14
#define ROOK_RED_1 8
#define ROOK_RED_2 15
#define QUEEN_RED 11
#define KING_RED 12

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
#define ROOK_BLUE_2 25
#define KNIGHT_BLUE_1 26
#define KNIGHT_BLUE_2 27
#define BISHOP_BLUE_1 28
#define BISHOP_BLUE_2 29
#define QUEEN_BLUE 30
#define KING_BLUE 31
enum Turn
{
	BLACK, 
	WHITE
};

#endif // !_CG_CONSTANTS_H_
