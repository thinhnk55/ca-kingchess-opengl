#ifndef _CG_SHIELD_H_
#define _CG_SHIELD_H_
#include <GL\freeglut.h>
#include "Model.h"
class ExtraModel : public Model
{
public:
	ExtraModel(void);
	ExtraModel(const ExtraModel* other);
	~ExtraModel(void);

	virtual void drawModel();
};

#endif
