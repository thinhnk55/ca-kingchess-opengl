#include "Shield.h"


Shield::Shield(void)
{
}

void Shield::drawModel()
{
	Model::drawModel();

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
	glPopMatrix();
}


Shield::~Shield(void)
{
}
