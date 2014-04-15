#ifndef _CG_INPUT_MANAGER_H_
#define _CG_INPUT_MANAGER_H_


#include "Light.h"
#include "Camera.h"
#include "Piece.h"

class KeyBoard
{
	bool fullscreen;
	int old_x, old_y, old_width, old_height;

public:
	KeyBoard(void);
	~KeyBoard(void);

	static KeyBoard& inst();
	void processKey(unsigned char key);
};

class Mouse
{
	bool mouseLeftDown;
	bool mouseRightDown;
	bool mouseMiddleDown;
	float mouseX, mouseY;

	void list_hits(GLint hits, GLuint *names);
	void gl_select(int x, int y);
	void mousedw(int x, int y, int but);

	void createRay(int x, int y);

public:
	Mouse(void);
	~Mouse(void);

	static Mouse& inst();
	void processMouse(int button, int state, int x, int y);
	void processMouseMotion(int x, int y);
	void processMousePassiveMotion(int x, int y);
};

#endif // !_CG_INPUT_MANAGER_H_
