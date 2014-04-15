#ifndef _CG_SPRITE_H_
#define _CG_SPRITE_H_

#include "SOIL/SOIL.h"
#include "mathlib.h"
#include "Constants.h"
#include "Geometry.h"

#include "GL/freeglut.h"

#include <iostream>

using namespace std;

class Sprite2D
{
	GLSYNTHESIZE(Vector2, mPos, Position);
	GLSYNTHESIZE(Vector2, mAnchor, AnchorPoint);
	GLSYNTHESIZE(int, mOpacity, Opacity);

	GLuint texID;
	bool mVisible;

	void loadTexture(const char *pszFilename);

public:

	int channel;
	Size size;

	Sprite2D(void);
	Sprite2D(const char* pFilename);
	~Sprite2D(void);

	static Sprite2D* create();
	static Sprite2D* create(const char* pFilename);

	void initWithFile(const char* pFilename);

	virtual void drawImg(Vector3 v1, Vector3 v2, Vector3 v3, Vector3 v4);
	virtual void drawImg();

	void setVisible(bool visible);
	bool isVisible();

	Rect boundingbox();
};  

inline void Sprite2D::setVisible(bool visible)
{
	mVisible = visible;
}

inline bool Sprite2D::isVisible()
{
	return mVisible;
}

#endif // !_CG_SPRITE_H_


