#ifndef _CG_SHIELD_H_
#define _CG_SHIELD_H_
#include <GL\freeglut.h>
#include "Model.h"
class ExtraModel : public Model
{
public:
    //mỗi boardcell sẽ có một chess piece đi kèm (tức là quân cờ đang đứng ở ô đấy)
    //nếu ko có thì biến này là NULL
    int associatedChessPieceIndex;
    int boardIndexX;
    int boardIndexY;

	ExtraModel(void);
	ExtraModel(const ExtraModel* other);
	~ExtraModel(void);

	virtual void drawModel();
};

#endif
