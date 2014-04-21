#ifndef _CG_CAMERA_H_INCLUDED
#define _CG_CAMERA_H_INCLUDED

#include <cmath>
#include "lib/mathlib.h"
#include <GL/freeglut.h>

class Camera {

public:
	const static float Radius;
	const static Vector3 origin;

	Vector2 zeroViewVector;

	Vector3 eye;
	Vector3 at;
	Vector3 up;

	float theta;
	float phi;
	float R;
	bool is_panning;
	bool is_rotating;
	float x_old;
	float y_old;
	float theta_old;
	float phi_old;

	Camera();
	~Camera();

	static Camera& inst();

	void update(float x, float y);
	void save(float x, float y);
	void zoom(float x);
	void pan(float x, float y);
	void rotate(float x, float y);
	void updateAngle();

private:
	Vector3 transf_coord();
};

#endif // _CG_CAMERA_H_INCLUDED
