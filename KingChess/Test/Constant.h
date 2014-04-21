#ifndef _CG_CONSTANTS_H_
#define _CG_CONSTANTS_H_

#define GLSYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }
;

#define PIECE_CIRCLE_SIZE 1.5

enum Turn
{
	BLACK, 
	WHITE
};

#endif // !_CG_CONSTANTS_H_
