#ifndef _CG_GRAPHIC_H_
#define _CG_GRAPHIC_H_

class Graphic
{

public:
	float screenWidth, screenHeight;
	float near_height;
	float zNear, zFar;

	Graphic(void);
	~Graphic(void);

	static Graphic& inst();
};

#endif // !_CG_GRAPHIC_H_
