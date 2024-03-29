#pragma once

#include "d3dx9.h"

class Object;
class QuadTree;
class Camera
{
public:
	float	x;
	float	y;
	float	vx;
	int		width;
	int		height;
	Object*	obj;			//Đối tượng được camera theo dõi.

	RECT	rect;
	Camera (float _x, float _y, float _width, float _height);
	void Update(float TPF,QuadTree* quadTree);
	void ResetRect();
};