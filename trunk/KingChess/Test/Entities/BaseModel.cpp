#include "BaseModel.h"




BaseModel::BaseModel(){

	zoomFactor = 1.0;
	mVisible = true;

	floorPlanePiece[0] = 0;
	floorPlanePiece[1] = 1;
	floorPlanePiece[2] = 0;
	floorPlanePiece[3] = 0;


	circleAngle = 0;

	mHighlight    = false;
	mShadow       = false;
	mSelected     = false;
	mDrawKnife    = false;
	mDrawShield   = false;

	mHighlightThickness =  1.0;
	mHighlightColor[0] = 0.0;
	mHighlightColor[1] = 1;
	mHighlightColor[2] = 0.0;
	mHighlightColor[3] = 0.5;


	mCircle = Sprite2D::create("images/circle.png");

	mKnife = new ExtraModel();
	mKnife->loadModel("Models/knife.obj");

	mShield = new ExtraModel();
	mShield->loadModel("Models/shield.obj");
}
BaseModel::BaseModel( const BaseModel* other )
{
	memcpy(this, other, sizeof(*other));
    this->mVisible = true;
    this->mSelected = false;
    this->mDrawKnife = false;
	this->mDrawShield = false;
}

BaseModel::~BaseModel(){

}

void BaseModel::drawModel(){
	if(!mVisible){
		return;
	}
	glPushMatrix();
	circleAngle += 0.6;
	if(circleAngle == 360){
		circleAngle = 0;
	}

	float x, y, z;
	getCenter(x, y, z);
	Model::drawModel();
	glScalef(zoomFactor, zoomFactor, zoomFactor);
	if (mSelected)
	{
		glColor4f(1, 1, 1, 1);
		glPushMatrix();
		glDisable(GL_LIGHTING);
		glTranslatef(mPos.x, mPos.y-getLength()*0.7, mPos.z);	
		glRotatef(circleAngle, 0, 1, 0);
		float size = getWidth() > getLength() ? getWidth()/2 : getLength()/2;
		mCircle->drawImg(Vector3( -PIECE_CIRCLE_SIZE*size, 0, -PIECE_CIRCLE_SIZE*size),
			Vector3( -PIECE_CIRCLE_SIZE*size, -0,  PIECE_CIRCLE_SIZE*size),
			Vector3(  PIECE_CIRCLE_SIZE*size, -0,  PIECE_CIRCLE_SIZE*size),
			Vector3(  PIECE_CIRCLE_SIZE*size, -0, -PIECE_CIRCLE_SIZE*size));
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}
	glPushMatrix();
	{
		// Move Object to coordinate origin
		glTranslatef(-x, -y, -z);
		float scaleX = (getWidth() + mHighlightThickness)/getWidth();
		float scaleY = (getHeight() + mHighlightThickness)/getHeight();
		float scaleZ = (getLength() + mHighlightThickness)/getLength();

		glPushMatrix();
		{
			glTranslated(mPos.x - mAnchor.x*getWidth(), 
				mPos.y - mAnchor.y*getHeight(),
				mPos.z - mAnchor.z*getLength());
			glRotatef(mAngleRotate, mRotateAxis.x, mRotateAxis.y, mRotateAxis.z);

			if (mDrawKnife)
			{
				glPushMatrix();
				glTranslatef(mAnchor.x*getWidth(), mAnchor.y*getHeight() + getHeight()*1.8, mAnchor.z*getLength());
				glScalef(2, 2, 2);
				mKnife->setAngleRotate(circleAngle);
				mKnife->drawModel();
				glPopMatrix(); 
			}

			if (mDrawShield)
			{
				glPushMatrix();
				glTranslatef(mAnchor.x*getWidth(), mAnchor.y*getHeight() + getHeight()*1.8, mAnchor.z*getLength());
				glScalef(2, 2, 2);
				mShield->setAngleRotate(circleAngle);
				mShield->drawModel();
				glPopMatrix(); 
			}

			if(mHighlight)
			{
				glEnable(GL_STENCIL_TEST);
				glStencilFunc(GL_ALWAYS, 0x0, 0x4);
				glStencilMask(0x4);
				glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
			}

			draw();

			if (mHighlight)
			{
				glStencilMask(0xffffffff);
				glClearStencil(0x4);

				glDisable(GL_LIGHTING);
				glEnable(GL_BLEND);
				glEnable(GL_STENCIL_TEST);
				glColor4f(mHighlightColor[0], mHighlightColor[1], mHighlightColor[2], mHighlightColor[3]);  /* 30% sorta yellow. */
				glStencilFunc(GL_EQUAL, 0x4, 0x4);
				glStencilMask(0x4);
				glStencilOp(GL_KEEP, GL_KEEP, GL_INVERT);

				glPushMatrix();
				glScalef(scaleX, scaleY, scaleZ);
				draw();
				glPopMatrix();

				glDisable(GL_BLEND);
				glDisable(GL_STENCIL_TEST);
				glEnable(GL_LIGHTING);
			}
		}
		glPopMatrix();

		if(mShadow)
		{
			glEnable(GL_STENCIL_TEST);
			glStencilFunc(GL_EQUAL, 0x4, 0x4);
			glStencilMask(0x4);
			glStencilOp(GL_KEEP, GL_KEEP, GL_INVERT);

			shadowMatrix(floorShadow, floorPlanePiece, Light::inst().getPosition());

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_LIGHTING);  /* Force the 50% black. */
			glColor4f(0.0, 0.0, 0.0, 0.3);

			glPushMatrix();
			{
				glTranslatef(-mAnchor.x*getWidth(), -mAnchor.y*getHeight() - 25, -mAnchor.z*getLength());
				/* Project the shadow. */
				glMultMatrixf((GLfloat *) floorShadow);
				glPushMatrix();
				{
					glTranslatef(mPos.x*(2-zoomFactor), mPos.y, mPos.z*(2-zoomFactor));
					draw();
				}
				glPopMatrix(); 
			}

			glPopMatrix();

			glDisable(GL_BLEND);
			glDisable(GL_STENCIL_TEST);
			glEnable(GL_LIGHTING);
		}    
	}
	glPopMatrix();
	glPopMatrix();
}

void BaseModel::setHighLightColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha){
	mHighlightColor[0] = red;
	mHighlightColor[1] = green;
	mHighlightColor[2] = blue;
	mHighlightColor[3] = alpha;
}

void BaseModel::moveUp(float delta){
	mPos.y += delta;	
	printf("mPos.y = %f", mPos.y);
}
void BaseModel::moveDown(float delta){
	mPos.y -= delta;
	printf("mPos.y = %f\n", mPos.y);
}
void BaseModel::moveLeft(float delta){
	mPos.x -= delta;
	printf("mPos.x = %f\n", mPos.x);
}
void BaseModel::moveRight(float delta){
	mPos.x += delta;
	printf("mPos.x = %f\n", mPos.x);
}
void BaseModel::moveIn(float delta){
	mPos.z -= delta;
	printf("mPos.z = %f\n", mPos.z);
}
void BaseModel::moveOut(float delta){
	mPos.z += delta;	
	printf("mPos.z = %f\n", mPos.z);
}