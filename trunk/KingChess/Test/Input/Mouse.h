#ifndef _MOUSE_H_
#define _MOUSE_H_

#include "GL/freeglut.h"
#include "../Sences/GameSence.h"

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


#endif // !_MOUSE_H_
