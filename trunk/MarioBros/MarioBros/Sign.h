#pragma once

#include "Animation.h"
#include "Sprite.h"
#include "Object.h"
#include <list>
using namespace std;

class Sign:public Object
{
public:
	Sign();
	Sign(float _x, float _y,float width,float height,int _ID);
	void Save(fstream *fs);
	void Load(fstream *fs);
};