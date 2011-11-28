#include "Object.h"
Object::Object()
{
	oldNode=NULL;
	sprite=NULL;
	ani=NULL;
	ResetRect();
}
Object::Object(float _xWorld, float _yWorld, float _width, float _height)
{
	x=_xWorld;
	y=_yWorld;
	width=_width;
	height=_height;
	oldNode=NULL;
	sprite=NULL;
	Huong=0;//k 1- trai qua 2 - phai qua
	ani=NULL;
	ResetRect();
}

void Object::ResetRect()
{
	rect.left=x;
	rect.top=y;
	rect.right=rect.left+width;
	rect.bottom=rect.top+height;
}
Object::~Object()
{
	if(ani!=NULL) delete ani;
};