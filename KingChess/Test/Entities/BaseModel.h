#ifndef _SAMPLE_MODEL_H_
#define _SAMPLE_MODEL_H_
#include "Model.h"
#include "ExtraModel.h"
#include "Sprite2D.h"

class BaseModel : public Model
{
public:

	BaseModel();
	~BaseModel();
	BaseModel(const BaseModel* other);


	GLSYNTHESIZE(GLfloat, mHighlightThickness, HighLightThickness);

	void drawModel();
	void setHighLightColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);

	void moveUp(float delta);
	void moveDown(float delta);
	void moveLeft(float delta);
	void moveRight(float delta);
	void moveIn(float delta);
	void moveOut(float delta);

	Sprite2D* mCircle;
	ExtraModel*    mKnife;
	ExtraModel*   mShield;
	bool      mDrawKnife;
	bool      mDrawShield;
    bool hasDoneFirstMove; //dung kiem tra quan tot co phai nuoc di dau tien cua no ko
    bool transformedToQueen;

	bool                mHighlight;
	GLfloat             mHighlightColor[4];
	bool                mSelected;
	bool                mShadow;
	float               floorShadow[4][4];

	GLfloat floorPlanePiece[4];
	float circleAngle;


private:

};
#endif // !_SAMPLE_MODEL_H
