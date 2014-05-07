#include "ExtraModel.h"



ExtraModel::ExtraModel(void)
{
	zoomFactor = 1.0;
	mVisible = true;
    associatedChessPieceIndex = -1;
    boardIndexX = -1;
    boardIndexY = -1;
}

ExtraModel::ExtraModel( const ExtraModel* other )
{
	memcpy(this, other, sizeof(*other));
}

void ExtraModel::drawModel()
{
	if(!mVisible){
		return;
	}

	float x, y, z;
	getCenter(x, y, z);

	glPushMatrix();
	// Move Object to coordinate origin
	glTranslatef(-x, -y, -z);
	glPushMatrix();
	glTranslated(mPos.x - mAnchor.x*getWidth(), 
		mPos.y - mAnchor.y*getHeight(),
		mPos.z - mAnchor.z*getLength());
	glRotatef(mAngleRotate, mRotateAxis.x, mRotateAxis.y, mRotateAxis.z);

	draw();

	glPopMatrix();
}


ExtraModel::~ExtraModel(void)
{
}
